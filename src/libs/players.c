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
    player->hand_size = 0;
    player->field_size = 0;
    player->deck_size = 0;
    player->discard_size = 0;
    return player;
}

void add_card_to_deck(Player* player, const char* card_name) {
    if (player->deck_size < DECK_SIZE) {
        Card* card_template = hash_map_get(ALL_CARDS, card_name);
        if (card_template) {
            Card* new_card = copy_card(card_template);
            player->deck[player->deck_size++] = new_card;
        }
    }
}

void draw_card(Player* player) {
    if (player->deck_size > 0 && player->hand_size < HAND_SIZE) {
        player->hand[player->hand_size++] = player->deck[--player->deck_size];
    }
}

int play_card(Player* player, size_t hand_index) {
    if (hand_index < player->hand_size) {
        Card* card = player->hand[hand_index];
        if (card && player->current_pips >= card->pip_cost) {
            player->current_pips -= card->pip_cost;
            player->field[player->field_size++] = card;

            // Shift remaining cards in hand to fill the gap
            for (size_t i = hand_index; i < player->hand_size - 1; ++i) {
                player->hand[i] = player->hand[i + 1];
            }
            player->hand_size--;
            return 1;
        }
    }
    return 0;
}

void discard_card(Player* player, size_t field_index) {
    if (field_index < player->field_size) {
        Card* card = player->field[field_index];
        player->discard[player->discard_size++] = card;

        // Shift remaining cards in field to fill the gap
        for (size_t i = field_index; i < player->field_size - 1; ++i) {
            player->field[i] = player->field[i + 1];
        }
        player->field_size--;
    }
}

void free_player(Player* player) {
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

