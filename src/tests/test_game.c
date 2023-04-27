#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "collections.h"
#include "color_print.h"
#include "players.h"
#include "game.h"

void test_init_game() {
    int success = init_game();
    assert(success == 0);
    Game* game = get_current_game();
    assert(game != NULL);
    assert(game->current_phase == DRAW_PHASE);
    assert(game->is_playing == false);
    assert(game->num_players == 0);
    assert(game->players != NULL);
    assert(game->turn_order.head == NULL);
    assert(game->turn_order.tail == NULL);
    assert(game->current_player_node == NULL);
}

void test_game_add_player() {
    Player* player = create_player("Alice");
    int success = game_add_player(player);
    assert(success == 0);
    Game* game = get_current_game();
    assert(game->num_players == 1);
    assert(hash_map_get(game->players, "Alice") != NULL);
    assert(game->turn_order.head != NULL);
    assert(game->turn_order.tail != NULL);
    assert(game->turn_order.head->data == player);
    assert(game->turn_order.tail->data == player);
}

void test_start_game() {
    int success = start_game();
    assert(success == 0);
    Game* game = get_current_game();
    assert(game->is_playing == true);
    assert(game->current_player_node != NULL);
    assert(game->current_player_node->data == game->turn_order.head->data);
}

// TODO: Implement other test functions for get_card_owner, get_target_card, etc.

int main() {
    test_init_game();
    test_game_add_player();
    test_start_game();

    printf("All tests passed!\n");
    return 0;
}
