#ifndef CARDS_H
#define CARDS_H

#include "collections.h"
#include "events.h"

#define MAX_CARDS 100

extern const char* ON_CARD_PLAYED_EVENT_NAME;
extern const char* ON_CARD_DRAWN_EVENT_NAME;
extern const char* ON_CARD_TARGETED_EVENT_NAME;
extern const char* ON_CARD_EFFECT_USED_EVENT_NAME;
extern const char* ON_CARD_DESTROYED_EVENT_NAME;
extern const char* ON_CARD_ATTACKED_EVENT_NAME;
extern const char* ON_CARD_DAMAGED_EVENT_NAME;
extern const char* ON_CARD_KILLED_EVENT_NAME;

extern HashMap* ALL_CARDS;

typedef struct {
    Callback played;
    Callback draw;
    Callback targeted;
    Callback effect_used;
    Callback destroyed;
    Callback attacked;
    Callback damaged;
    Callback killed;
} Callbacks;

typedef struct {
    const char* name;
    const char* description;
    const char* effect;

    Callbacks on;

    int pip_cost;
    int attack;
    int defense;

} Card;

Card* copy_card(Card* original);
void setup_card(Card* card);
void init_cards();


#endif // CARDS_H