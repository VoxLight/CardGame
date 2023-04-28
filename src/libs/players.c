// players.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "players.h"
#include "cards.h"
#include "events.h"
#include "color_print.h"

Player* create_player(const char* name) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->name = name;

    player->max_health = 10;
    player->current_health = 10;

    player->max_pips = 3;
    player->current_pips = 3;

    player->hand_size = 0;
    player->field_size = 0;
    player->deck_size = 0;
    player->discard_size = 0;
    return player;
}

void shuffle_deck(Player* player) {
    srand(time(NULL));

    // Shuffle the deck using Fisher-Yates shuffle algorithm
    for (int i = player->deck_size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card* temp = player->deck[i];
        player->deck[i] = player->deck[j];
        player->deck[j] = temp;
    }
}

void reset_player(Player* player) {
    player->current_health = player->max_health;
    player->current_pips = player->max_pips;

    for (; player->hand_size != 0;)
        player->deck[player->deck_size++] = player->hand[--player->hand_size];

    for (; player->field_size != 0;)
        player->deck[player->deck_size++] = player->field[--player->field_size];

    for (; player->discard_size != 0;)
        player->deck[player->deck_size++] = player->discard[--player->discard_size];

}

void print_player_state(Player* player, bool deck_hidden) {
    printf("\n");
    print_colored(COLOR_PRINT_YELLOW, "Player: %s\n", player->name);
    print_colored(COLOR_PRINT_MAGENTA, "Health: %d\n", player->current_health);
    print_colored(COLOR_PRINT_BLUE, "Current pips: %d\n", player->current_pips);
    print_colored(COLOR_PRINT_GREEN, "Hand Size: %ld\n", player->hand_size);
    for (int i = 0; i < player->hand_size; i++) {
        Card* card = player->hand[i];
        print_colored(COLOR_PRINT_YELLOW, "[%d]", i);
        print_card(card);
    }
    printf("Field Size: %ld\n", player->field_size);
    for (int i = 0; i < player->field_size; i++) {
        Card* card = player->field[i];
        print_colored(COLOR_PRINT_YELLOW, "[%d]", i);
        print_card(card);
    }
    printf("Deck size: %ld\n", player->deck_size);
    if (!deck_hidden) {
        for (int i = 0; i < player->deck_size; i++) {
            Card* card = player->deck[i];
            print_colored(COLOR_PRINT_YELLOW, "[%d]", i);
            print_card(card);
        }
    }
    printf("Discard size: %ld\n", player->discard_size);
    for (int i = 0; i < player->discard_size; i++) {
        Card* card = player->discard[i];
        print_colored(COLOR_PRINT_YELLOW, "[%d]", i);
        print_card(card);
    }
    puts("");
}

void player_set_attack_and_effect_ready(Player* player) {
    player->current_pips = player->max_pips;
    for (int i = 0; i < player->field_size; i++) {
        player->field[i]->attack_ready = true;
        player->field[i]->effect_ready = true;
    }
}

// Note about how add_card_to_deck and draw_card work.
// We don't remove the cards from the deck, but instead
// we use the index to keep track of where we are. Add
// will increase the index and draw decrements the index,
// so it should always be balanced.
int add_card_to_deck(Player* player, const char* card_name) {
    if (player->deck_size >= DECK_SIZE) {
        print_colored(COLOR_PRINT_RED, "The '%s' was not added to the deck because the deck is full.", card_name);
        return -1;
    }
    Card* card_template = hash_map_get(ALL_CARDS, card_name);
    if (card_template == NULL) {
        print_colored(COLOR_PRINT_RED, "Failed to create copy of '%s'.", card_name);
        return -2;
    }
    Card* new_card = copy_card(card_template);
    player->deck[player->deck_size++] = new_card;
    //print_colored(COLOR_PRINT_BLUE, "Card '%s' (address: %p) added to %s's DECK.\n", player->deck[player->deck_size-1]->name, player->deck[player->deck_size-1], player->name);
    return 0;
}

int add_card_to_field(Player* player, const char* card_name) {
    if (player->field_size >= DECK_SIZE) {
        print_colored(COLOR_PRINT_RED, "The '%s' was not summoned because the field is full.", card_name);
        return -1;
    }

    Card* card_template = hash_map_get(ALL_CARDS, card_name);
    if (card_template == NULL) {
        print_colored(COLOR_PRINT_RED, "Failed to create copy of '%s'.", card_name);
        return -2;
    }

    Card* new_card = copy_card(card_template);
    player->field[player->field_size++] = new_card;
    //print_colored(COLOR_PRINT_BLUE, "Card '%s' (address: %p) added to %s's FIELD.\n", player->field[player->field_size-1]->name, player->field[player->field_size-1], player->name);
    // Question on whether this should trigger the card played event
    // Maybe it should.
    trigger_event(ON_CARD_PLAYED_EVENT_NAME, player->field[player->field_size-1], player);
    return 0;
}

int draw_card_from_deck(Player* player) {
    if(player->deck_size == 0) {
        print_colored(COLOR_PRINT_RED, "No more cards in %s's deck.\n", player->name);
        return -2;
    }
    if(player->hand_size == HAND_SIZE){
        print_colored(COLOR_PRINT_RED, "%s already has %d cards in hand. Cannot draw more.\n",
        player->name, HAND_SIZE);
        return -1;
    }

    player->hand[player->hand_size++] = player->deck[--player->deck_size];
    //print_colored(COLOR_PRINT_BLUE, "Card '%s' (address: %p) added to %s's HAND.\n", player->hand[player->hand_size-1]->name, player->hand[player->hand_size-1], player->name);
    trigger_event(ON_CARD_DRAWN_EVENT_NAME, player->hand[player->hand_size-1], player);
    return 0;
}

int play_card_from_hand(Player* player, size_t hand_index) {
    // -2 Gameplay / Rule error
    // -1 Usage error
    if (player->field_size == DECK_SIZE){
        print_colored(COLOR_PRINT_RED, "%s has too many cards on field, unable to play more.\n", player->name);
        return -2;
    }

    if(hand_index >= player->hand_size){
        print_colored(COLOR_PRINT_RED, "%d is out of range of %s's hand.\n", hand_index, player->name);
        return -1;
    }

    Card* card = player->hand[hand_index];

    if(card->pip_cost > player->current_pips){
        print_colored(COLOR_PRINT_RED, "%s has %d pips. Need %d pips to play %s\n", 
        player->name, player->current_pips, card->pip_cost, card->name);
        return -2;
    }
          
    player->current_pips -= card->pip_cost;
    player->field[player->field_size++] = card;
    //print_colored(COLOR_PRINT_BLUE, "Card '%s' (address: %p) played by %s.\n", player->field[player->field_size-1]->name, player->field[player->field_size-1], player->name);
    trigger_event(ON_CARD_PLAYED_EVENT_NAME, player->field[player->field_size-1], player);
    

    // Shift remaining cards in hand to fill the gap
    for (size_t i = hand_index; i < player->hand_size - 1; ++i) {
        player->hand[i] = player->hand[i + 1];
    }
    player->hand_size--;
    return 0;
}

size_t get_card_index_in_location(Card* card, Card** location, size_t location_size) {
    for (size_t i = 0; i < location_size; i++) {
        if (location[i] == card) return i;
    }
    return location_size; // Indicates that the card was not found in the location
}

int kill_card_on_field(Player* player, size_t field_index) {
    if (field_index >= player->field_size){
        print_colored(COLOR_PRINT_RED, "%d is not an index on %s's field.\n", field_index, player->name);
        return -1;
    }
    Card* card = player->field[field_index];
    player->discard[player->discard_size++] = card;
    //print_colored(COLOR_PRINT_BLUE, "Card '%s' (address: %p) was killed, poor %s.\n", player->discard[player->discard_size-1]->name, player->discard[player->discard_size-1], player->name);
    trigger_event(ON_CARD_KILLED_EVENT_NAME, player->discard[player->discard_size-1], player);

    // Shift remaining cards in field to fill the gap
    for (size_t i = field_index; i < player->field_size - 1; ++i) {
        player->field[i] = player->field[i + 1];
    }
    player->field_size--;
}

int free_player(Player* player) {
    if (player) {
        for (size_t i = 0; i < player->hand_size; ++i) {
            free_card(player->hand[i]);
        }

        for (size_t i = 0; i < player->field_size; ++i) {
            free_card(player->field[i]);
        }

        for (size_t i = 0; i < player->deck_size; ++i) {
            free_card(player->deck[i]);
        }

        for (size_t i = 0; i < player->discard_size; ++i) {
            free_card(player->discard[i]);
        }

        free(player);
    }
}

int player_owns_card(Player* player, Card* card) {
    const int OWNER_DECK = 0b1;
    const int OWNER_HAND = 0b100;
    const int OWNER_DISCARD = 0b10000;
    const int OWNER_FIELD = 0b1000000;

    for (int i = 0; i < player->field_size; i++) {
        if (player->field[i] == card) return OWNER_FIELD;
    }

    for (int i = 0; i < player->deck_size; i++){
        if (player->deck[i] == card) return OWNER_DECK;
    }   

    for (int i = 0; i < player->discard_size; i++) {
        if (player->discard[i] == card) return OWNER_DISCARD;
    }

    for (int i = 0; i < player->hand_size; i++) {
        if (player->hand[i] == card) return OWNER_HAND;
    }

    return 0;
}

