#include <stdio.h>

#include "game.h"

int main(){

    Game* game = new_game();
    if(game == NULL){
        printf("NULL\n");
        return 0;
    }
    printf("%p\n", game);
    printf("%p\n", game->current_phase);
    printf("%d\n", game->current_phase);

    printf("%d\n", game->players);
    // if(game->current_phase == NULL){

    //     printf("NULL\n");
    //     return 0;

    // }
    // printf("%s, %d, %p\n", 
    //     game->current_phase, game->current_phase,  game->current_phase
    // );

    return 0;
}
