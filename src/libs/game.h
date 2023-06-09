#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "players.h"
#include "collections.h"

#define MAX_PLAYERS 2

extern const char* ON_PHASE_CHANGE_EVENT_NAME;

typedef enum {
    OWNER_DECK      = 0b1,
    ANY_DECK        = 0b10,
    OWNER_HAND      = 0b100,
    ANY_HAND        = 0b1000,
    OWNER_DISCARD   = 0b10000,
    ANY_DISCARD     = 0b100000,
    OWNER_FIELD     = 0b1000000,
    ANY_FIELD       = 0b10000000,
} CardLocation;

typedef enum {
    DRAW_PHASE,
    MAIN_PHASE,
    BATTLE_PHASE,
    __num_phases,
} TurnPhase;


typedef struct {

    TurnPhase current_phase;
    
    bool is_playing;

    int num_players;

    HashMap* players;

    LinkedList* turn_order;

    LinkedListNode* current_player_node;

} Game;

/**
 * @brief Iteratively calls all the print commands of the players in the game.
 * 
 * @return -1 if something went wrong. 0 otherwise.
 */
int print_current_game_state();

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
 * @brief Ends the game.
 * 
 * @param game The game to end.
 */
void end_game();

/**
 * @brief Steps the game phase and turn order by one.
 * 
 * @return 0 for success.
 */
int step_current_game();

/**
 * @brief Gets the player that owns the given card.
 * 
 * @param game The game to search for the card in.
 * @param card The card to find the owner of.
 * 
 * @return A pointer to the player that owns the card.
 */
Player* get_card_owner(Card* card);

/**
 * @brief Prompts the player to select a number of cards from the given locations.
 * 
 * 
 */
//Card* get_target_card(Player* owner, unsigned int card_locations);

/**
 * @brief Two cards battle each other.
 * 
 * @param attacker The attacking card.
 * @param defender The defending card.
 * 
 * @return 0 if the battle was a draw, 1 if the attacker won, -1 if the defender won, 2 if both cards died.
 */
int card_battle(Card* attacker, Card* defender);



#endif // GAME_H
