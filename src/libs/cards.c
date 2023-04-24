#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "collections.h"
#include "cards.h"

// Card*, Player*
const char* ON_CARD_PLAYED_EVENT_NAME       = "on_card_played";


const char* ON_CARD_DRAWN_EVENT_NAME        = "on_card_drawn";


const char* ON_CARD_TARGETED_EVENT_NAME     = "on_card_targeted";
const char* ON_CARD_EFFECT_USED_EVENT_NAME  = "on_card_effect_used";
const char* ON_CARD_ATTACKED_EVENT_NAME     = "on_card_attacked";
const char* ON_CARD_DAMAGED_EVENT_NAME      = "on_card_damaged";
const char* ON_CARD_KILLED_EVENT_NAME       = "on_card_killed";

// create in main
HashMap* ALL_CARDS;

typedef struct Player Player;

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

void _big_bad_wolf_damaged(va_list args){
    Card* target_card = va_arg(args, Card*);
    // Player* target_player = va_arg(args, Player*);

    Card* base_card = hash_map_get(ALL_CARDS, target_card->name);
    if (target_card->attack >= base_card->attack+3) return;
    target_card->attack++;
    puts("The big bad wolf gained an attack.");

}

static Card BIG_BAD_WOLF = {
    .name = "Big Bad Wolf",
    .description = "A tall wolf who stands on two legs. He will give you to the count of three before he blows your house away!",

    .effect = "This card gains 1 attack each time it survives combat. Stacks up to 3 times.",

    .on.damaged = (Callback)_big_bad_wolf_damaged,

    .pip_cost = 3,
    .attack = 3,
    .defense = 4,
};

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
    create_event(ON_CARD_PLAYED_EVENT_NAME);

    ALL_CARDS = hash_map_create(MAX_CARDS);

    hash_map_put(ALL_CARDS, LARGE_SLIME.name, &LARGE_SLIME);
    hash_map_put(ALL_CARDS, HARMLESS_BAT.name, &HARMLESS_BAT);
    hash_map_put(ALL_CARDS, BIG_BAD_WOLF.name, &BIG_BAD_WOLF);


    Card* large_slime = hash_map_get(ALL_CARDS, "Large Slime");
}

void free_cards() {
    for (size_t i = 0; i < ALL_CARDS->size; ++i) {
        Card* card = ALL_CARDS->table[i]->value;
        free_card(card);
    }
    hash_map_free(ALL_CARDS);
}

void free_card(Card* card) {
    if (card) {
        free(card);
    }
}
