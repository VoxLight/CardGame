#include <stdio.h>

#include "game.h"

int main(){

    int success = new_game();
    if(success == -1){
        printf("Error making game.\n");
        return 0;
    }
    Game* game = get_current_game();
    printf("%p\n", game);
    printf("%p\n", game->current_phase);
    printf("%d\n", game->current_phase);
    printf("Players: %d\n", game->players->size);

    return 0;
}
