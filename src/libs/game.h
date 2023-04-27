#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "players.h"
#include "collections.h"

#define MAX_PLAYERS 2

typedef enum {
    OWNER_DECK      = 0b1,
    ANY_DECK        = 0b10,
    OWNER_HAND      = 0b100,
    ANY_HAND        = 0b1000,
    OWNER_DISCARD   = 0b10000,
    ANY_DISCARD     = 0b100000,
} CardLocation;

typedef enum {
    DRAW_PHASE,
    MAIN_PHASE,
    BATTLE_PHASE,
} TurnPhase;


typedef struct {

    TurnPhase current_phase;
    
    bool is_playing;

    HashMap* players;

    LinkedList turn_order;

    LinkedListNode* current_player_node;

} Game;

/**
 * @brief Creates a new Game struct in memory and returns it.
 * 
 * @return A pointer to the newly created Game struct.
 */
int init_game();

/**
 * @brief Gets the current game.
 * 
 * @return A pointer to the current game.
 */
Game* get_current_game();

/**
 * @brief Adds a player to the game.
 * 
 * @param game The game to add the player to.
 * @param player The player to add to the game.
 * 
 * @return 0 if the player was added successfully, -1 if there was an error.
*/
int game_add_player(Player* player);

/**
 * @brief Starts a new game with the CURRENT_GAME.
 * 
 * @return 0 if the game start succeeded, -1 if there was an error.
 */
int start_game();

/**
 * @brief Gets the player that owns the given card.
 * 
 * @param game The game to search for the card in.
 * @param card The card to find the owner of.
 * 
 * @return A pointer to the player that owns the card.
 */
Player* get_card_owner(Card* card);



#endif // GAME_H
