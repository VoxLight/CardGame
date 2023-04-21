#ifndef CARD_DEFINITIONS_C
#define CARD_DEFINITIONS_C
#include "cards.h"
#include "players.h"

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

#endif // CARD_DEFINITIONS_C