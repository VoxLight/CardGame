// test_player.c
#include <stdio.h>
#include "cards.h"
#include "players.h"

int main() {
    // Initialize the card library
    init_cards();

    // Create a player with a max of 5 pips
    Player* player = create_player("Alice");

    // Add cards to the player's deck
    add_card_to_deck(player, "Harmless Bat");
    add_card_to_deck(player, "Small Slime");
    add_card_to_deck(player, "Big Bad Wolf");
    add_card_to_deck(player, "Large Slime");

    printf("Player state after adding cards:\n");
    print_player_state(player);

    // Draw two cards
    draw_card(player);
    draw_card(player);

    printf("\nPlayer state after drawing two cards:\n");
    print_player_state(player);

    // Play the first card from the hand
    int success = play_card(player, 0);
    printf("\nPlaying card: %d\n", 1);

    success = play_card(player, 0);
    printf("\nPlaying card: %d\n", success);

    print_player_state(player);

    // Discard the first card from the field
    discard_card(player, 0);
    printf("\nPlayer state after discarding a card from the field:\n");
    print_player_state(player);

    // Free the player memory
    free_player(player);

    return 0;
}
