#include <stdio.h>
#include <stdlib.h>


#include "console.h"
#include "events.h"
#include "color_print.h"
#include "cards.h"
#include "players.h"
#include "game.h"

void cmd_ping(char* command_name, char** args){
   print_colored(COLOR_PRINT_YELLOW, "[%s]Pong!\n", command_name);
}

void cmd_echo(char* command_name, char** args) {
    if (args[0] == NULL) {
        print_colored(COLOR_PRINT_RED, "[%s]No message to echo.\n", command_name);
        return;
    }
    for (int i = 0; args[i] != NULL; i++) {
        print_colored(COLOR_PRINT_GREEN, "[%s]Arg %d: %s\n", command_name, i, args[i]);
    }
    puts("");
}

void cmd_card_info(char* command_name, char** args) {
    Card* card;
    if (args[0] == NULL) {
        print_colored(COLOR_PRINT_YELLOW, "[%s]No card name specified. Printing all cards.\n", command_name);
        for (int i = 0; i < ALL_CARDS->size; i++) {
            if (ALL_CARDS->table[i] == NULL) continue;
            Card* card = (Card*)(ALL_CARDS->table[i]->value);
            print_card(card);
        }
    }
    else {
        Card* card = hash_map_get(ALL_CARDS, args[0]);
        if (card == NULL) {
            print_colored(COLOR_PRINT_RED, "[%s]Card \"%s\" not found.\n", command_name, args[0]);
            return;
        }
        print_card(card);
    }

}

void cmd_add_player(char* command_name, char** args) {
    if (args[0] == NULL) {
        print_colored(COLOR_PRINT_RED, "[%s]Player not created. No player name specified.\n", command_name);
        return;
    }
    Player* player = create_player(args[0]);
    if (player == NULL) {
        print_colored(COLOR_PRINT_RED, "[%s]Failed to create player \"%s\".\n", command_name, args[0]);
        return;
    }
    if (game_add_player(player) == 0)
        print_colored(COLOR_PRINT_GREEN, "[%s]Created player \"%s\".\n", command_name, player->name);
}

void cmd_game_info() {
    print_current_game_state();
}

void cmd_add_card_player_deck(char* command_name, char** args) {
    if (args[0] == NULL || args[1] == NULL) {
        print_colored(COLOR_PRINT_RED, "[%s]Player/card name NOT specified.\n", command_name);
        return;
    }

    if (get_current_game()->is_playing) {
        print_colored(COLOR_PRINT_RED, "[%s]Cannot add cards while a game is in progress.\n", command_name);
        return;
    }

    Player* player = hash_map_get(get_current_game()->players, args[0]);
    if (player == NULL) {
        print_colored(COLOR_PRINT_RED, "[%s]Player \"%s\" not found.\n", command_name, args[0]);
        return;
    }
    Card* card = hash_map_get(ALL_CARDS, args[1]);
    if (card == NULL) {
        print_colored(COLOR_PRINT_RED, "[%s]Card \"%s\" not found.\n", command_name, args[1]);
        return;
    }
    if (add_card_to_deck(player, args[1]) == 0) {
        print_colored(COLOR_PRINT_GREEN, "[%s]Added card \"%s\" to player \"%s\".\n", command_name, card->name, player->name);
    }
}

void cmd_start_game() {
    start_game();
}

void cmd_end_game() {
    end_game();
}

void cmd_step_game() {
    step_current_game();
}

void cmd_card_battle(char* command_name, char** args) {
    if (get_current_game()->current_phase != BATTLE_PHASE) {
        print_colored(COLOR_PRINT_RED, "[%s]You can only attack during your Battle Phase.\n", command_name);
        return;
    }
    if (args[0] == NULL) {
        print_colored(COLOR_PRINT_RED, "[%s]You must specify the index of attacker and target, or attacker when opponent has no cards.\n", command_name);
        return;
    }
    if (args[1] == NULL && ((Player*)(get_current_game()->current_player_node->next->data))->field_size > 0) {
        print_colored(COLOR_PRINT_RED, "[%s]Opponent has cards, you must attack a card on the field.\n", command_name);
        return;
    }
    // This is all so messy and should be cleaned up ASAP.
    if (args[1] == NULL) {
        int index = atoi(args[0]);
        if (index >= ((Player*)get_current_game()->current_player_node->data)->field_size){
			print_colored(COLOR_PRINT_RED, "[%s]%d is not a valid index.\n", command_name, index);
			return;
		}
        // TODO: Make this an event.
        Player* opponent = get_current_game()->current_player_node->next->data;
        Card* attacker = ((Player*)get_current_game()->current_player_node->data)->field[index];
        if (!attacker->attack_ready) {
            print_colored(COLOR_PRINT_RED, "%s's attack is not ready. Must wait 1 turn after summoning to attack.\n", attacker->name);
            return;
        }
        print_colored(COLOR_PRINT_RED, "[%s]%s is attacked directly by %s and loses 1 hp.\n", command_name, opponent->name, attacker->name);
        opponent->current_health--;
        return;
    }
    int attacker_index = atoi(args[0]);
    int defender_index = atoi(args[1]);
    Card* attacker = ((Player*)get_current_game()->current_player_node->data)->field[attacker_index];
    Card* defender = ((Player*)get_current_game()->current_player_node->next->data)->field[defender_index];
    card_battle(attacker, defender);

}

void cmd_player_info(char* command_name, char** args) {
    if (args[0] == NULL) {
		print_colored(COLOR_PRINT_RED, "[%s]Player name NOT specified.\n", command_name);
		return;
	}
    Player* player = hash_map_get(get_current_game()->players, args[0]);
    if (player == NULL) {
        print_colored(COLOR_PRINT_RED, "[%s]Player not found.\n", command_name);
        return;
    }
    print_player_state(player, get_current_game()->is_playing);
}

void cmd_play_card(char* command_name, char** args) {
    if (args[0] == NULL) {
		print_colored(COLOR_PRINT_RED, "[%s]Hand index NOT specified.\n", command_name);
		return;
	}
    if (get_current_game()->current_phase != MAIN_PHASE) {
        print_colored(COLOR_PRINT_RED, "[%s]You can only play cards on your main phase.\n", command_name);
        return;
    }
    int hand_index = atoi(args[0]);
    play_card_from_hand(get_current_game()->current_player_node->data, hand_index);

    
}

void cmd_activate_effect(char* command_name, char** args) {
    if (args[0] == NULL) {
        print_colored(COLOR_PRINT_RED, "[%s]Card index NOT specified.\n", command_name);
        return;
    }
    if (get_current_game()->current_phase != MAIN_PHASE) {
		print_colored(COLOR_PRINT_RED, "[%s]You can only activate effects on your main phase.\n", command_name);
		return;
	}
    Player* player = get_current_game()->current_player_node->data;
    int card_index = atoi(args[0]);
    trigger_event(ON_CARD_EFFECT_USED_EVENT_NAME, player->field[card_index], player);
}

int main(){
    init_cards();
    init_console();
    init_game();

    register_command("ping", "Tests if commands are working.", "ping", cmd_ping);
    register_command("echo", "Prints the message.", "echo <message1> <message2> ...", cmd_echo);
    register_command("card", "Prints information about the cards. Optionally, specify a card name for that card's info.", "card \"<card name>\"", cmd_card_info);
    register_command("create_player", "Make a new player.", "create_player \"<player name>\"", cmd_add_player);
    register_command("game_info", "Prints the state of the current game.", "game_info", cmd_game_info);
    register_command("add_card", "Adds a card to a player's deck.", "add_card \"<player name>\" \"<card name>\"", cmd_add_card_player_deck);
    register_command("start", "Start the game in the current state.", "start", cmd_start_game);
    register_command("end", "Ends the current game and resets back to the state before starting.", "end", cmd_end_game);
    register_command("step", "This is how you indicate you are done with your current phase, and move to the next phase.", "step", cmd_step_game);
    register_command("player", "Prints information about a player.", "player \"<player name>\"", cmd_player_info);
    register_command("play", "Plays a card from your hand.", "play <hand index>", cmd_play_card);
    register_command("battle", "Make one of your cards attack a card (or your opponent if no cards are on the field). Just pass your card index to attack the opponent.", "battle <field index> (field index)", cmd_card_battle);


    start_console_loop();
    return 0;
}