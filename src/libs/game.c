#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


// TODO: Remove this include
#include <assert.h>

#include "collections.h"
#include "color_print.h"
#include "events.h"
#include "game.h"


Game* CURRENT_GAME;

const char* ON_PHASE_CHANGE_EVENT_NAME = "on_phase_change";

bool _current_game_exists(){
    return CURRENT_GAME != NULL;
}

int make_new_game() {
    Game* game = (Game*)malloc(sizeof(Game));
    if (game == NULL) return -1;
    game->current_phase = DRAW_PHASE;
    game->is_playing = false;
    game->num_players = 0;
    game->players = hash_map_create(MAX_PLAYERS);
    game->turn_order = create_linked_list();
    CURRENT_GAME = game;
    return 0;
}

void end_game(){
    // This will reset the game back to an empty state.
    for (int i = 0; i < CURRENT_GAME->players->size; i++) {
        Player* player = CURRENT_GAME->players->table[i]->value;
        if (player) reset_player(player);
    }

    CURRENT_GAME->is_playing = false;
    CURRENT_GAME->current_phase = DRAW_PHASE;
}

int step_current_game() {
    if (!CURRENT_GAME->is_playing) {
        print_colored(COLOR_PRINT_RED, "Cannot step a game that has not been started.");
        return -1;
    }
    //print_colored(COLOR_PRINT_BLUE, "Phase '%d' -> '%d'.\n", CURRENT_GAME->current_phase, (CURRENT_GAME->current_phase + 1) % __num_phases);
    CURRENT_GAME->current_phase = (CURRENT_GAME->current_phase + 1) % __num_phases;
    
    trigger_event(ON_PHASE_CHANGE_EVENT_NAME);
    return 0;
}

char* _phase_string(TurnPhase phase) {
    switch (CURRENT_GAME->current_phase) {

    case DRAW_PHASE:
        return "Draw Phase";

    case MAIN_PHASE:
        return "Main Phase";

    case BATTLE_PHASE:
        return "Battle Phase";
    }

}

void _handle_on_phase_changed() {
    print_colored(COLOR_PRINT_CYAN, "Phase changed to %s.\n", _phase_string(CURRENT_GAME->current_phase));
    switch (CURRENT_GAME->current_phase) {

        case DRAW_PHASE:
            CURRENT_GAME->current_player_node = CURRENT_GAME->current_player_node->next;
            print_colored(COLOR_PRINT_CYAN, "It is now %s's turn.\n", ((Player*)CURRENT_GAME->current_player_node->data)->name);
            //print_colored(COLOR_PRINT_CYAN, "Turn Change: '%s' -> '%s'\n", ((Player*)CURRENT_GAME->current_player_node->data)->name, ((Player*)CURRENT_GAME->current_player_node->next->data)->name);
            draw_card_from_deck(CURRENT_GAME->current_player_node->data);
            break;

        case MAIN_PHASE:
			break;

        case BATTLE_PHASE:
            break;
    }
}

int init_game(){
    create_event(ON_PHASE_CHANGE_EVENT_NAME);
    register_callback(ON_PHASE_CHANGE_EVENT_NAME, (Callback)_handle_on_phase_changed);
    if (_current_game_exists()) end_game();
    make_new_game();
    return 0;
}

int print_current_game_state(){
    if(!_current_game_exists()){
        print_colored(
            COLOR_PRINT_RED, 
            "Unable to print current game state. No game has been initialized.\n"
        );
        return -1;
    }
    print_colored(COLOR_PRINT_YELLOW, "Current Game State:\n");
    print_colored(COLOR_PRINT_GREEN, "Phase: %s\n", _phase_string(CURRENT_GAME->current_phase));
    print_colored(COLOR_PRINT_BLUE, "Player Count: %d\n", CURRENT_GAME->num_players);
    if(CURRENT_GAME->is_playing)
        print_colored(COLOR_PRINT_YELLOW, "%s's Turn.\n", ((Player*)CURRENT_GAME->current_player_node->data)->name);

    for (int i = 0; i < CURRENT_GAME->players->size; i++) {
        if (CURRENT_GAME->players->table[i] == NULL) continue;
        print_player_state(CURRENT_GAME->players->table[i]->value, CURRENT_GAME->is_playing);
    }
    return 0;
}

Game* get_current_game(){
    return CURRENT_GAME;
}

int game_add_player(Player* player){
    if(!_current_game_exists()){
        print_colored(
            COLOR_PRINT_RED, 
            "Unable to add player to game. No game has been initialized.\n"
        );
        return -1;
    }
    if(CURRENT_GAME->is_playing){
        print_colored(
            COLOR_PRINT_RED, 
            "The game has already started. You cannot add players to a game that has already started.\n"
        );
        return -2;
    }
    if(CURRENT_GAME->num_players >= MAX_PLAYERS){
        print_colored(
            COLOR_PRINT_RED, 
            "Unable to add player to game. The game is full.\n"
        );
        return -3;
    }
    if(hash_map_get(CURRENT_GAME->players, player->name) != NULL){
        print_colored(
            COLOR_PRINT_RED, 
            "Unable to add player to game. A player with the name \"%s\" already exists.\n", 
            player->name
        );
        return -4;
    }

    // Easy Lookup for players by name
    hash_map_put(CURRENT_GAME->players, player->name, player);

    linked_list_append(CURRENT_GAME->turn_order, player);

    CURRENT_GAME->num_players++;

    return 0;
}

int start_game(){
    if(CURRENT_GAME->num_players == 0){
        print_colored(
            COLOR_PRINT_RED, 
            "Unable to start the game when there are no players in the game.\n"
        );
        return -1;
    }
    CURRENT_GAME->is_playing = true;
    CURRENT_GAME->turn_order->tail->next = CURRENT_GAME->turn_order->head;
    CURRENT_GAME->current_player_node = CURRENT_GAME->turn_order->head;
    for (int i = 0; i < CURRENT_GAME->num_players; i++){
        // Must check for null in the hash map.
        Player* player = CURRENT_GAME->players->table[i]->value;
        if(player) shuffle_deck(player);
    }
    trigger_event(ON_PHASE_CHANGE_EVENT_NAME);

    return 0;
}

Player* get_card_owner(Card* card){
    for (int i = 0; i < CURRENT_GAME->players->size; i++) {
        Player* player = CURRENT_GAME->players->table[i]->value;
        if (player && player_owns_card(player, card)) return player;
    }
    return NULL;
}

int card_battle(Card* attacker, Card* defender) {
    attacker->defense -= defender->attack;
    defender->defense -= attacker->attack;
    if (attacker->defense <= 0) {
        Card* original_attacker = (Card*)hash_map_get(ALL_CARDS, attacker->name);
        *attacker = *original_attacker;
        kill_card_on_field(get_card_owner(attacker), get_card_index_in_location(attacker, get_card_owner(attacker)->field, get_card_owner(attacker)->field_size));
    }
    if (defender->defense <= 0) {
        Card* original_defender = (Card*)hash_map_get(ALL_CARDS, defender->name);
        *defender = *original_defender;
        kill_card_on_field(get_card_owner(defender), get_card_index_in_location(defender, get_card_owner(defender)->field, get_card_owner(defender)->field_size));
    }

    return 0;
};


