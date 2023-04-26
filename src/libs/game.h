#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "players.h"
#include "collections.h"


typedef enum {
    DRAW_PHASE,
    MAIN_PHASE,
    BATTLE_PHASE,
} TurnPhase;


typedef struct {

    TurnPhase current_phase;
    
    bool is_playing;


    LinkedList players;

} Game;

/**
 * @brief Creates a new Game struct in memory and returns it.
 * 
 * @return A pointer to the newly created Game struct.
 */
Game* new_game();

/**
 * @brief Adds a player to the game.
 * 
 * @param game The game to add the player to.
 * @param player The player to add to the game.
 * 
 * @return 0 if the player was added successfully, -1 if there was an error.
*/
int game_add_player(Game* game, Player* player);

/**
 * @brief Starts a new game with the given Game struct.
 * 
 * @return 0 if the game start succeeded, -1 if there was an error.
 */
int start_game(Game* game);



#endif // GAME_H
