/**
 * @file players.h
 * @brief This header file contains the declarations of functions and struct for the Player entity.
 */

#ifndef PLAYERS_H
#define PLAYERS_H

#include <stddef.h> // for size_t
#include <stdbool.h> // for bool

#include "cards.h" // for Card

#define DECK_SIZE 20 /**< The size of the deck of cards for the Player */
#define STARTING_HAND_SIZE 5 /**< The size of the starting hand of cards for the Player */
#define HAND_SIZE 10 /**< The size of the hand of cards for the Player */

/**
 * @struct Player
 * @brief This struct represents the Player entity in the game.
 */
typedef struct {
    const char* name; /**< The name of the Player */

    int max_health; /**< The maximum health that the Player can have */
    int current_health; /**< The current health of the Player */
    
    int max_pips; /**< The maximum pips that the Player can have */
    int current_pips; /**< The current number of pips that the Player has */

    size_t hand_size; /**< The size of the Player's hand */
    Card* hand[HAND_SIZE]; /**< The array of cards in the Player's hand */

    size_t field_size; /**< The size of the Player's field */
    Card* field[DECK_SIZE]; /**< The array of cards in the Player's field */

    size_t deck_size; /**< The size of the Player's deck */
    Card* deck[DECK_SIZE]; /**< The array of cards in the Player's deck */
    
    size_t discard_size; /**< The size of the Player's discard pile */
    Card* discard[DECK_SIZE]; /**< The array of cards in the Player's discard pile */
} Player;

/**
 * @brief Creates a new Player with the specified name.
 * 
 * @param name The name of the new Player.
 * @return A pointer to the newly created Player, or NULL if an error occurred.
 */
Player* create_player(const char* name);

/**
 * @brief Shuffles the deck of the specified Player.
 * 
 * @param player The Player whose deck will be shuffled.
 */
void shuffle_deck(Player* player);

/**
 * @brief Resets the specified Player's health and pips to their maximum values as well as putting all cards back into the deck.
 * 
 * @param player The Player to reset.
 */
void reset_player(Player* player);

/**
 * @brief Prints the state of the specified Player.
 * 
 * @param player The Player to print the state of.
 */
void print_player_state(Player* player, bool deck_hidden);


/**
 * @brief Sets all cards, on the specified Player's field, attack and effect ready flags to true.
 * 
 * @param player The Player whose card's flags will be set.
 */
void player_set_attack_and_effect_ready(Player* player);

/**
 * @brief Adds a card with the specified name to the deck of the specified Player.
 * 
 * @param player The Player whose deck the card will be added to.
 * @param card_name The name of the card to be added.
 * 
 * @return 0 if the card was successfully added, or -1 if an error occurred.
 */
int add_card_to_deck(Player* player, const char* card_name);

/**
 * @brief Removes the card at the specified index from the specified Player's deck.
 * 
 * @param player The Player whose deck the card will be removed from.
 * @param index The index of the card to be removed.
 * 
 * @return The removed card, or NULL if an error occurred.
 */
size_t get_card_index_in_location(Card* card, Card** location, size_t location_size);

/**
 * @brief Adds a card with the specified name to the field of the specified Player.
 * 
 * @param player The Player whose field the card will be added to.
 * @param card_name The name of the card to be added.
 * @return 0 if the card was successfully added, -1 if field is full, -2 if the card was not found.
*/
int add_card_to_field(Player* player, const char* card_name);

/**
 * @brief Draws a card from the deck of the specified Player and adds it to their hand.
 * 
 * @param player The Player who is drawing a card.
 * @return 0 if a card was successfully drawn, -1 if there are no cards left in the deck, or -2 if an error occurred.
 */
int draw_card_from_deck(Player* player);

/**
 * @brief Plays the card at the specified index in the specified Player's hand and adds it to their field.
 * 
 * @param player The Player who is playing a card.
 * @param hand_index The index of the card in the Player's hand to be played.
 * @return 0 if the card was successfully played, or -1 if an error occurred.
 */
int play_card_from_hand(Player* player, size_t hand_index);

/**
 * @brief Discards the card at the specified index in the specified Player's field and adds it to their discard pile.
 * 
 * @param player The Player who is discarding a card.
 * @param field_index The index of the card in the Player's field to be discarded.
 * @return 0 if the card was successfully discarded, or -1 if an error occurred.
 */
int kill_card_on_field(Player* player, size_t field_index);

/**
 * @brief Frees the memory used by the specified Player.
 * 
 * @param player The Player to be freed.
 * @return 0 if the memory was successfully freed, or -1 if an error occurred.
 */
int free_player(Player* player);

/**
 * @brief Checks if the specified Player has a card instance in their card locations.
 * 
 * @param player The Player to check.
 * @param card The card instance to check for.
 * 
 * @return true if the Player has no cards in their deck, false otherwise.
 */
int player_owns_card(Player* player, Card* card);

#endif // PLAYERS_H
