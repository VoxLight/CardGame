#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "collections.h"
#include "events.h"
#include "cards.h"

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

void setup_card(Card* card){
    puts("Setting up Default Event Handlers");
    printf("%s", card->name);

}

Card* copy_card(Card* original){
    Card* copy = malloc(sizeof(Card));
    if (copy != NULL){
        memcpy(copy, original, sizeof(Card));
        return copy;
    }
    return NULL;
}

void init_cards(){
    ALL_CARDS = hash_map_create(MAX_CARDS);

    hash_map_put(ALL_CARDS, LARGE_SLIME.name, &LARGE_SLIME);
    hash_map_put(ALL_CARDS, HARMLESS_BAT.name, &HARMLESS_BAT);
    hash_map_put(ALL_CARDS, BIG_BAD_WOLF.name, &BIG_BAD_WOLF);


    Card* large_slime = hash_map_get(ALL_CARDS, "Large Slime");
}