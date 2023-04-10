#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "collections.h"
#include "events.h"
#include "cards.h"
#include "players.h"

const char* ON_CARD_PLAYED_EVENT_NAME       = "on_card_played";
const char* ON_CARD_DRAWN_EVENT_NAME        = "on_card_drawn";
const char* ON_CARD_TARGETED_EVENT_NAME     = "on_card_targeted";
const char* ON_CARD_EFFECT_USED_EVENT_NAME  = "on_card_effect_used";
const char* ON_CARD_DESTROYED_EVENT_NAME    = "on_card_destroyed";
const char* ON_CARD_ATTACKED_EVENT_NAME     = "on_card_attacked";
const char* ON_CARD_DAMAGED_EVENT_NAME      = "on_card_damaged";
const char* ON_CARD_KILLED_EVENT_NAME       = "on_card_killed";

// create in main
HashMap* ALL_CARDS;

void setup_card(Card* card, Player* owner){
    puts("Setting up Default Event Handlers");
    printf("%s", card->name);

    // Initialize the data of the card
    card->owner = owner;

}

Card* copy_card(Card* original){
    Card* copy = malloc(sizeof(Card));
    if (copy != NULL){
        memcpy(copy, original, sizeof(Card));
        return copy;
    }
    return NULL;
}


void _large_slime_played(va_list args){
    Card* slime = va_arg(args, Card*);
    printf("%s was played.", slime->name);
}

static Card LARGE_SLIME = {
    .name = "Large Slime",
    .description = "A Large Gooey Slime. It appears to be made of a strange substance that is not water.",
    .effect = "When Large Slime is targeted, create a 'Small Slime'(/1/1) token on the field.",

    .on.played = (Callback)_large_slime_played,

    .pip_cost = 1,
    .attack = 1,
    .defense = 1,
};


void _harmless_bat_effect_activated(va_list args){
    Card* target_card = va_arg(args, Card*);
    Player* target_player = va_arg(args, Player*);
    puts("Harmless Bat effect activated");
}

static Card HARMLESS_BAT = {
    .name = "Harmless Bat",
    .description = "A small flying bat that inhabits caves and forests that busies itself munching on wild fruits.",
    .effect = "Can use 1 pip to restore 1 life to target player once per turn.",

    .on.effect_used = (Callback)_harmless_bat_effect_activated,

    .pip_cost = 2,
    .attack = 0,
    .defense = 4,
};

void init_cards(){
    ALL_CARDS = hash_map_create(MAX_CARDS);

    hash_map_put(ALL_CARDS, LARGE_SLIME.name, &LARGE_SLIME);
    hash_map_put(ALL_CARDS, HARMLESS_BAT.name, &HARMLESS_BAT);


    Card* large_slime = hash_map_get(ALL_CARDS, "Large Slime");
}