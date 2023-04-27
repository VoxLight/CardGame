#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "collections.h"
#include "cards.h"
#include "color_print.h"
#include "players.h"
#include "game.h"

// Card*, Player*
const char* ON_CARD_PLAYED_EVENT_NAME       = "on_card_played";

// Card*, Player*
const char* ON_CARD_DRAWN_EVENT_NAME        = "on_card_drawn";

const char* ON_CARD_TARGETED_EVENT_NAME     = "on_card_targeted";
const char* ON_CARD_EFFECT_USED_EVENT_NAME  = "on_card_effect_used";
const char* ON_CARD_ATTACK_EVENT_NAME       = "on_card_attacked";
const char* ON_CARD_DAMAGED_EVENT_NAME      = "on_card_damaged";
const char* ON_CARD_KILLED_EVENT_NAME       = "on_card_killed";

HashMap* ALL_CARDS;


//void _lily_fat_cat_played(va_list args){
//    Card* card = va_arg(args, Card*);
//    Player* owner = va_arg(args, Player*);
//
//    // // target a card
//    
//    Card* target_card = get_target_card();
//    // // find the owner of the target card
//    // // copy .on from target_card to card
//    // memcpy(card->on, target_card->on);
//    // strcpy(target_card->effect, card->effect);
//
//}
//
//
//static Card LILY_FAT_CAT = {
//    .name = "Lily, the Fat Cat",
//    .description = "placeholder description",
//    .effect = "When Summoned, can devour 1 card on either field. Lily, the Fat Cat gains the effect(s) of the devoured card.",
//
//    .on.played = (Callback)_lily_fat_cat_played,
//
//    .pip_cost = 3,
//    .attack = 3,
//    .defense = 3,
//
//};


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

static Card SMALL_SLIME = {
    .name = "Small Slime",
    .description = "A small gooey slime. It appears to be made of a strange substance that is not water.",
    .effect = "No Effect.",

    .pip_cost = 0,
    .attack = 1,
    .defense = 1,

};

void _large_slime_killed(va_list args){
    Card* slime = va_arg(args, Card*);
    Player* player = va_arg(args, Player*);
    add_card_to_field(player, SMALL_SLIME.name);
    add_card_to_field(player, SMALL_SLIME.name);

}

static Card LARGE_SLIME = {
    .name = "Large Slime",
    .description = "A large gooey slime. It appears to be made of a strange substance that is not water.",
    .effect = "When Large Slime is killed, create 2 'Small Slime'(0*/1/1) tokens on the field.",

    .on.killed = (Callback)_large_slime_killed,

    .pip_cost = 2,
    .attack = 1,
    .defense = 1,
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

Card* copy_card(Card* original) {
    Card* copy = malloc(sizeof(Card));
    if (copy != NULL) {
        // Copy the non-string fields
        copy->on = original->on;
        copy->pip_cost = original->pip_cost;
        copy->attack = original->attack;
        copy->defense = original->defense;

        // Allocate and copy the string fields
        copy->name = strdup(original->name);
        copy->description = strdup(original->description);
        copy->effect = strdup(original->effect);

        return copy;
    }
    return NULL;
}

int card_battle(Card* attacker, Card* defender){
    if(!attacker->attack_ready) return -1;

    print_colored(COLOR_PRINT_BLUE, 
        "Card '%s' (address: %p) attacked Card '%s' (adress: %p).\n", 
        attacker->name, attacker, defender->name, defender
    );

    // Attacker attacks defender


}

void on_card_played(va_list args){
    va_list args_copy;
    va_copy(args_copy, args);
    Card* card = va_arg(args, Card*);
    Player* player = va_arg(args, Player*);
    
    print_colored(COLOR_PRINT_CYAN, "%s was played.\n", card->name);
    if(card->on.played == NULL) return;
    print_colored(COLOR_PRINT_CYAN, "%s\n", card->effect);
    card->on.played(args_copy);
}

void on_card_drawn(va_list args){
    va_list args_copy;
    va_copy(args_copy, args);
    Card* card = va_arg(args, Card*);
    Player* player = va_arg(args, Player*);

    print_colored(COLOR_PRINT_CYAN, "%s was drawn.\n", card->name);
    if(card->on.draw == NULL) return;
    print_colored(COLOR_PRINT_CYAN, "%s\n", card->effect);
    card->on.draw(args_copy);
}

void on_card_killed(va_list args){
    va_list args_copy;
    va_copy(args_copy, args);
    Card* card = va_arg(args, Card*);
    Player* player = va_arg(args, Player*);

    print_colored(COLOR_PRINT_CYAN, "%s was killed.\n", card->name);
    if(card->on.killed == NULL) return;
    print_colored(COLOR_PRINT_CYAN, "%s\n", card->effect);
    card->on.killed(args_copy);
}

void on_card_effect_used(va_list args){
    va_list args_copy;
    va_copy(args_copy, args);
    Card* card = va_arg(args, Card*);
    Card* other_card = va_arg(args, Card*);
    print_colored(COLOR_PRINT_CYAN, "%s was used.\n", card->name);

    if(card->on.effect_used == NULL) return;
    print_colored(COLOR_PRINT_CYAN, "%s\n", card->effect); 
    card->on.effect_used(args_copy);
}

void on_card_attacked(va_list args){
    va_list args_copy;
    va_copy(args_copy, args);
    Card* card = va_arg(args, Card*);
    Card* other_card = va_arg(args, Card*);
    print_colored(COLOR_PRINT_CYAN, "%s was used.\n", card->name);
    if(card->on.attack == NULL) return;
    print_colored(COLOR_PRINT_CYAN, "%s\n", card->effect);
    card->on.attack(args_copy);
}

void on_card_damaged(va_list args){
    va_list args_copy;
    va_copy(args_copy, args);
    Card* card = va_arg(args, Card*);
    Card* other_card = va_arg(args, Card*);
    print_colored(COLOR_PRINT_CYAN, "%s was damaged.\n", card->name);
    if(card->on.damaged == NULL) return;
    print_colored(COLOR_PRINT_CYAN, "%s\n", card->effect);
    card->on.damaged(args_copy);
}

void init_cards(){

    create_event(ON_CARD_PLAYED_EVENT_NAME);
    register_callback(ON_CARD_PLAYED_EVENT_NAME, (Callback)on_card_played);

    create_event(ON_CARD_DRAWN_EVENT_NAME);
    register_callback(ON_CARD_DRAWN_EVENT_NAME, (Callback)on_card_drawn);

    create_event(ON_CARD_EFFECT_USED_EVENT_NAME);
    register_callback(ON_CARD_EFFECT_USED_EVENT_NAME, (Callback)on_card_effect_used);

    create_event(ON_CARD_ATTACK_EVENT_NAME);
    register_callback(ON_CARD_ATTACK_EVENT_NAME, (Callback)on_card_attacked);

    create_event(ON_CARD_DAMAGED_EVENT_NAME);
    register_callback(ON_CARD_DAMAGED_EVENT_NAME, (Callback)on_card_damaged);

    create_event(ON_CARD_KILLED_EVENT_NAME);
    register_callback(ON_CARD_KILLED_EVENT_NAME, (Callback)on_card_killed);


    ALL_CARDS = hash_map_create(MAX_CARDS);
    hash_map_put(ALL_CARDS, LARGE_SLIME.name, &LARGE_SLIME);
    hash_map_put(ALL_CARDS, SMALL_SLIME.name, &SMALL_SLIME);
    hash_map_put(ALL_CARDS, HARMLESS_BAT.name, &HARMLESS_BAT);
    hash_map_put(ALL_CARDS, BIG_BAD_WOLF.name, &BIG_BAD_WOLF);
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

void print_card(Card* card){
    print_colored(COLOR_PRINT_YELLOW, "%s ", card->name);
    printf("(");
    print_colored(COLOR_PRINT_CYAN, "%d*", card->pip_cost);
    printf("/");
    print_colored(COLOR_PRINT_RED, "%d", card->attack);
    printf("/");
    print_colored(COLOR_PRINT_GREEN, "%d", card->defense);
    printf(")\n");
    print_colored(COLOR_PRINT_MAGENTA, "    Description:");
    printf(" %s\n", card->description);
    print_colored(COLOR_PRINT_MAGENTA, "    Effect:");
    printf(" %s\n", card->effect);
}
