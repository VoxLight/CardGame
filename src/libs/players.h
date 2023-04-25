// players.h
#ifndef PLAYERS_H
#define PLAYERS_H

#include <stddef.h> // for size_t
#include "cards.h"

#define DECK_SIZE 20
#define HAND_SIZE 7

typedef struct {
    const char* name;
    int max_pips;
    int current_pips;
    size_t hand_size;
    size_t field_size;
    size_t deck_size;
    size_t discard_size;
    Card* hand[HAND_SIZE];
    Card* field[DECK_SIZE];
    Card* deck[DECK_SIZE];
    Card* discard[DECK_SIZE];
} Player;

Player* create_player(const char* name);
void print_player_state(Player* player);
int add_card_to_deck(Player* player, const char* card_name);
int draw_card(Player* player);
int play_card(Player* player, size_t hand_index);
int discard_card(Player* player, size_t field_index);
int free_player(Player* player);

#endif // PLAYERS_H
