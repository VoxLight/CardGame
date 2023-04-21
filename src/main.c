#include <stdio.h>

#include "console.h"
#include "events.h"
#include "cards.h"
#include "color_print.h"

void cmd_ping(char* command_name, char** args){
    printf("Pong!\n");
}

void cmd_echo(char* command_name, char** args) {
    //printf("%s ", message); // would include "echo ...."=
    // printf("%s %s %s %s %s", args[0], args[1], args[2], args[3], args[4]);
    if (args[0] == NULL) {
        printf("No message to echo.\n");
        return;
    }
    for (int i = 0; args[i] != NULL; i++) {
        printf("Arg %d: %s\n", i, args[i]);
    }
    puts("");
}

void _print_card(Card* card){
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

void cmd_card_info(char* command_name, char** args){
    Card* card;
    if (args[0] == NULL) {
        printf("No card name specified. Printing all cards.\n");
        for (int i = 0; i < ALL_CARDS->size; i++) {
            if(ALL_CARDS->table[i] == NULL) continue;
            Card* card = (Card*)(ALL_CARDS->table[i]->value);
            _print_card(card);
        }
    }else {
        Card* card = hash_map_get(ALL_CARDS, args[0]);
        if (card == NULL) {
            printf("Card \"%s\" not found.\n", args[0]);
            return;
        }
        _print_card(card);
    }

}

int main(){
    init_cards();
    init_console();

    register_command("ping", "Tests if commands are working.", "ping", cmd_ping);
    register_command("echo", "Prints the message.", "echo <message>", cmd_echo);
    register_command("card", "Prints information about the cards. Optionally, specify a card name for that card's info.", "card (\"card name\")", cmd_card_info);

    start_console_loop();
    return 0;
}