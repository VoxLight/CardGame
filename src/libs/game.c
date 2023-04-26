#include <stdlib.h>

#include "game.h"
#include "color_print.h"

Game* new_game(){
    Game* game = (Game*)malloc(sizeof(Game*) * 1);
    game->current_phase = DRAW_PHASE;
    game->is_playing = false;
    game->players = create_linked_list();
    return game;
}

int start_game(Game* game){
    if(game->players.size == 0){
        print_colored(
            COLOR_PRINT_RED, 
            "Unable to start the game when there are no players in the game.\n"
        );
        return -1;
    }
    game->is_playing = true;

    return 0;
}

int game_add_player(Game* game, Player* player){
    if(game->is_playing){
        print_colored(
            COLOR_PRINT_RED, 
            "The game has already started. You cannot add players to a game that has already started.\n"
        );
        return -1;
    }
    linked_list_append(&game->players, player);
    return 0;
}

