#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "console.h"
#include "events.h"

void cmd_ping(char* message, char** args){
    printf("Pong!\n");
}

int main(){
    init_console();

    register_command("ping", "Tests if commands are working.", "ping", cmd_ping);

    start_console_loop();
    return 0;
}