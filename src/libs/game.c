#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// TODO: Remove this include
#include <assert.h>

#include "collections.h"
#include "color_print.h"
#include "game.h"


Game* CURRENT_GAME;

bool _current_game_exists(){
    return CURRENT_GAME != NULL;
}

void _destroy_game(Game* game){
    free(game);
}

int print_current_game_state(){
    if(!_current_game_exists()){
        print_colored(
            COLOR_PRINT_RED, 
            "Unable to print current game state. No game has been initialized.\n"
        );
        return -1;
    }
    print_colored(COLOR_PRINT_YELLOW, "Current game state:\n");
}

int init_game(){
    if(_current_game_exists()) _destroy_game(CURRENT_GAME);
    Game* game = (Game*)malloc(sizeof(Game));
    if(game == NULL) return -1;
    game->current_phase = DRAW_PHASE;
    game->is_playing = false;
    game->num_players = 0;
    game->players = hash_map_create(MAX_PLAYERS);
    game->turn_order = create_linked_list();
    CURRENT_GAME = game;
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

    linked_list_append(&(CURRENT_GAME->turn_order), player);

    CURRENT_GAME->num_players++;

    return 0;
}

int start_game(){
    if(CURRENT_GAME->players->size == 0){
        print_colored(
            COLOR_PRINT_RED, 
            "Unable to start the game when there are no players in the game.\n"
        );
        return -1;
    }
    CURRENT_GAME->is_playing = true;
    CURRENT_GAME->turn_order.tail->next = CURRENT_GAME->turn_order.head;
    CURRENT_GAME->current_player_node = CURRENT_GAME->turn_order.head;

    return 0;
}

Player* get_card_owner(Card* card){
    assert(0 > 1);
    return (Player*)NULL;
}

Card* get_target_card(Player* owner, unsigned int card_locations){
    assert(0 > 1);
    return (Card*)NULL;
}


