#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#include "cards.h"
#include "players.h"

void activate_effect_used(Card* card, ...){
    va_list args;
    va_start(args, card);
    card->on.effect_used(args);
    va_end(args);
}

void activate_played(Card* card, ...){
    va_list args;
    va_start(args, card);
    card->on.played(args);
    va_end(args);
}

void test_large_slime_played_callback() {
    Card* large_slime = CARDS[0];
    Player player;

    // Initialize the Large Slime card and player
    setup_card(large_slime, &player);

    // Simulate the card being played
    activate_played(large_slime, large_slime);

    // Your test cases here to validate the state of the card, player, or any other related data
}

void test_harmless_bat_effect_activated_callback() {
    Card* harmless_bat = CARDS[1];
    Player player;

    // Initialize the Harmless Bat card and player
    setup_card(harmless_bat, &player);


    // Simulate the card effect being activated
    activate_effect_used(harmless_bat, harmless_bat);


    // Your test cases here to validate the state of the card, player, or any other related data

}

void test_copy_card() {
    Card* harmless_bat = CARDS[1];
    Card* copy = copy_card(harmless_bat);

    // Your test cases here to validate the state of the card, player, or any other related data
    assert(copy != NULL);
    assert(copy != harmless_bat);
    assert(copy->name == harmless_bat->name);

    free(copy);
}

int main() {
    test_large_slime_played_callback();
    test_harmless_bat_effect_activated_callback();
    printf("All tests passed.\n");
    return 0;
}
