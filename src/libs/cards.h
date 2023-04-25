/**
 * @file cards.h
 * @brief This header file contains the declarations of functions and structs for handling cards.
 */

#ifndef CARDS_H
#define CARDS_H

#include "collections.h"
#include "events.h"

#define MAX_CARDS 100 /**< The maximum number of cards that can exist in the game */

extern const char* ON_CARD_PLAYED_EVENT_NAME; /**< The name of the event that is triggered when a card is played */
extern const char* ON_CARD_DRAWN_EVENT_NAME; /**< The name of the event that is triggered when a card is drawn */
extern const char* ON_CARD_TARGETED_EVENT_NAME; /**< The name of the event that is triggered when a card is targeted */
extern const char* ON_CARD_EFFECT_USED_EVENT_NAME; /**< The name of the event that is triggered when a card's effect is used */
extern const char* ON_CARD_ATTACKED_EVENT_NAME; /**< The name of the event that is triggered when a card is attacked */
extern const char* ON_CARD_DAMAGED_EVENT_NAME; /**< The name of the event that is triggered when a card is damaged */
extern const char* ON_CARD_KILLED_EVENT_NAME; /**< The name of the event that is triggered when a card is killed */

extern HashMap* ALL_CARDS; /**< A hash map containing all the cards in the game */

/**
 * @struct Handlers
 * @brief A structure that holds callbacks for various card events.
 */
typedef struct {
    Callback played; /**< The callback function to be called when the card is played */
    Callback draw; /**< The callback function to be called when the card is drawn */
    Callback targeted; /**< The callback function to be called when the card is targeted */
    Callback effect_used; /**< The callback function to be called when the card's effect is used */
    Callback destroyed; /**< The callback function to be called when the card is destroyed */
    Callback attacked; /**< The callback function to be called when the card is attacked */
    Callback damaged; /**< The callback function to be called when the card is damaged */
    Callback killed; /**< The callback function to be called when the card is killed */
} Handlers;

/**
 * @struct Card
 * @brief A structure that represents a card in the game.
 */
typedef struct {
    const char* name; /**< The name of the card */
    const char* description; /**< The description of the card */
    const char* effect; /**< The effect of the card */

    Handlers on; /**< The handlers for the card events */

    int pip_cost; /**< The pip cost of the card */
    int attack; /**< The attack value of the card */
    int defense; /**< The defense value of the card */

} Card;

/**
 * @brief Creates a copy of the specified card.
 * 
 * @param original The original card to be copied.
 * @return A pointer to the newly created card, or NULL if an error occurred.
 */
Card* copy_card(Card* original);

/**
 * @brief Initializes all the cards in the game.
 */
void init_cards();

/**
 * @brief Frees all the memory used by the cards in the game.
 */
void free_cards();

/**
 * @brief Frees the memory used by the specified card.
 * 
 * @param card The card to be freed.
 */
void free_card(Card* card);

/**
 * @brief Prints the specified card.
 * 
 * @param card The card to be printed.
 */
void print_card(Card* card);

#endif // CARDS_H
