// players.h
#ifndef PLAYERS_H
#define PLAYERS_H

#include "collections.h"
#include "cards.h"

typedef struct {
    const char* name;
    int max_pips;
    int current_pips;
    LinkedList hand;
    LinkedList field;
    LinkedList deck;
    LinkedList discard;
} Player;

Player* create_player(const char* name, int max_pips);
void add_card_to_deck(Player* player, const char* card_name);
void draw_card(Player* player);
int play_card(Player* player, int hand_index);
void discard_card(Player* player, int field_index);
void free_player(Player* player);

#endif // PLAYERS_H
