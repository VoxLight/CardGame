// test_player.c
#include <stdio.h>

#include "cards.c"

void print_player_state(Player* player) {
    printf("Player: %s\n", player->name);
    printf("Current pips: %d\n", player->current_pips);
    printf("Hand:\n");
    for (int i = 0; i < player->hand.size; i++) {
        Card* card = linked_list_remove(&player->hand, i);
        printf("  %s\n", card->name);
    }
    printf("Field:\n");
    for (int i = 0; i < player->field.size; i++) {
        Card* card = linked_list_remove(&player->field, i);
        printf("  %s\n", card->name);
    }
    printf("Deck size: %d\n", player->deck.size);
    printf("Discard size: %d\n", player->discard.size);
}

int main() {
    // Initialize the card library
    init_cards();

    // Create a player with a max of 5 pips
    Player* player = create_player("Alice", 5);

    // Add cards to the player's deck
    add_card_to_deck(player, "Basic Card A");
    add_card_to_deck(player, "Basic Card B");
    add_card_to_deck(player, "Basic Card A");
    add_card_to_deck(player, "Basic Card C");

    printf("Player state after adding cards:\n");
    print_player_state(player);

    // Draw two cards
    draw_card(player);
    draw_card(player);

    printf("\nPlayer state after drawing two cards:\n");
    print_player_state(player);

    // Play the first card from the hand
    int success = play_card(player, 0);
    printf("\nPlaying card: %s\n", success ? "Success" : "Failed");
    print_player_state(player);

    // Discard the first card from the field
    discard_card(player, 0);
    printf("\nPlayer state after discarding a card from the field:\n");
    print_player_state(player);

    // Free the player memory
    free_player(player);

    return 0;
}
