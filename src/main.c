#include <stdio.h>

#include "console.h"
#include "events.h"
#include "color_print.h"
#include "cards.h"
#include "players.h"
#include "game.h"

void cmd_ping(char* command_name, char** args){
   print_colored(COLOR_PRINT_YELLOW, "Pong!\n");
}

void cmd_echo(char* command_name, char** args) {
    //printf("%s ", message); // would include "echo ...."=
    // printf("%s %s %s %s %s", args[0], args[1], args[2], args[3], args[4]);
    if (args[0] == NULL) {
        print_colored(COLOR_PRINT_RED, "No message to echo.\n");
        return;
    }
    for (int i = 0; args[i] != NULL; i++) {
        print_colored(COLOR_PRINT_GREEN, "Arg %d: %s\n", i, args[i]);
    }
    puts("");
}

void cmd_card_info(char* command_name, char** args){
    Card* card;
    if (args[0] == NULL) {
        print_colored(COLOR_PRINT_YELLOW, "No card name specified. Printing all cards.\n");
        for (int i = 0; i < ALL_CARDS->size; i++) {
            if(ALL_CARDS->table[i] == NULL) continue;
            Card* card = (Card*)(ALL_CARDS->table[i]->value);
            print_card(card);
        }
    }else {
        Card* card = hash_map_get(ALL_CARDS, args[0]);
        if (card == NULL) {
            print_colored(COLOR_PRINT_RED, "Card \"%s\" not found.\n", args[0]);
            return;
        }
        print_card(card);
    }

}

void cmd_add_player(char* command_name, char** args){
    if (args[0] == NULL) {
        print_colored(COLOR_PRINT_RED, "Player not created. No player name specified.\n");
        return;
    }
    Player* player = new_player(args[0]);
    if (player == NULL) {
        print_colored(COLOR_PRINT_RED, "Failed to create player \"%s\".\n", args[0]);
        return;
    }
    print_colored(COLOR_PRINT_GREEN, "Created player \"%s\".\n", player->name);
}

void cmd_game_info(){
    
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

    start_console_loop();
    return 0;
}