#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "cards.h"
#include "players.h"
#include "collections.h"

void activate_effect_used(Card* card, ...) {
    if (card->on.effect_used) {
        va_list args;
        va_start(args, card);
        card->on.effect_used(args);
        va_end(args);
    }
}

void activate_played(Card* card, ...) {
    if (card->on.played) {
        va_list args;
        va_start(args, card);
        card->on.played(args);
        va_end(args);
    }
}

void activate_damaged(Card* card, ...) {
    if (card->on.damaged) {
        va_list args;
        va_start(args, card);
        card->on.damaged(args);
        va_end(args);
    }
}

void test_callbacks() {
    init_cards();

    HashMap* all_cards = ALL_CARDS;
    for (size_t i = 0; i < all_cards->size; i++) {
        HashNode* node = all_cards->table[i];
        while (node) {
            Card* card = (Card*)node->value;

            // Initialize the card and player
            setup_card(card);

            // Simulate the card being played
            activate_played(card, card);

            // Simulate the card effect being activated
            activate_effect_used(card, card);

            // Simulate the card being damaged
            activate_damaged(card, card);

            node = node->next;
        }
    }
}

void test_copy_card() {
    init_cards();

    Card* harmless_bat = hash_map_get(ALL_CARDS, "Harmless Bat");
    Card* copy = copy_card(harmless_bat);

    // Your test cases here to validate the state of the card, player, or any other related data
    assert(copy != NULL);
    assert(copy != harmless_bat);
    assert(copy->name == harmless_bat->name);

    free(copy);
}

int main() {
    test_callbacks();
    test_copy_card();
    printf("All tests passed.\n");
    return 0;
}
