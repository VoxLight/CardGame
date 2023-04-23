// players.c
#include <stdlib.h>
#include <stdio.h>

#include "players.h"
#include "cards.h"

Player* create_player(const char* name, int max_pips) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->name = name;
    player->max_pips = max_pips;
    player->current_pips = max_pips;
    player->hand = (Card**)malloc(sizeof(Card*) * HAND_SIZE);
    player->field = (Card**)malloc(sizeof(Card*) * DECK_SIZE);
    player->deck = (Card**)malloc(sizeof(Card*) * DECK_SIZE);
    player->discard = (Card**)malloc(sizeof(Card*) * DECK_SIZE);
    return player;
}

void add_card_to_deck(Player* player, const char* card_name) {
    Card* card_template = hash_map_get(ALL_CARDS, card_name);
    if (card_template) {
        Card* new_card = copy_card(card_template);
        linked_list_append(&player->deck, new_card);
    }
}

void draw_card(Player* player) {
    Card* card = linked_list_remove(&player->deck, 0);
    if (card) {
        linked_list_append(&player->hand, card);
    }
}

int play_card(Player* player, int hand_index) {
    Card* card = linked_list_remove(&player->hand, hand_index);
    if (card && player->current_pips >= card->pip_cost) {
        player->current_pips -= card->pip_cost;
        linked_list_append(&player->field, card);
        return 1;
    }
    return 0;
}

void discard_card(Player* player, int field_index) {
    Card* card = linked_list_remove(&player->field, field_index);
    if (card) {
        linked_list_append(&player->discard, card);
    }
}

void free_player(Player* player) {
    destroy_linked_list(&player->hand);
    destroy_linked_list(&player->field);
    destroy_linked_list(&player->deck);
    destroy_linked_list(&player->discard);
    free(player);
}
