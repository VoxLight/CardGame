#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include "events.h"

typedef struct {
    char* name;
} MockCard;

void on_card_draw(va_list args) {
    MockCard* drawn_card = va_arg(args, MockCard*);
    printf("Card drawn: %s\n", drawn_card->name);
}

void on_card_draw_2(va_list args) {
    MockCard* drawn_card = va_arg(args, MockCard*);
    printf("Card drawn: %s\n", drawn_card->name);
}

void on_card_death(va_list args) {
    MockCard* slain_card = va_arg(args, MockCard*);
    MockCard* slayer_card = va_arg(args, MockCard*);
    printf("%s killed %s\n", slayer_card->name, slain_card->name);
}

int main() {
    // Test create_event
    create_event("card_draw");
    create_event("card_death");

    Callback draw_handler_1 = on_card_draw;
    Callback draw_handler_2 = on_card_draw_2;
    assert(register_callback("card_draw", draw_handler_1) == 0);
    assert(register_callback("card_draw", draw_handler_2) == 0);

    
    Callback death_handler;
    death_handler = on_card_death;
    assert(register_callback("card_death", death_handler) == 0);

    // Test trigger_event
    MockCard drawn_card = {.name = "Test Card"};
    MockCard slain_card = {.name = "Slain Card"};
    MockCard slayer_card = {.name = "Slayer Card"};

    trigger_event("card_draw", &drawn_card);
    trigger_event("card_death", &slain_card, &slayer_card);

    // Test unregister_callback
    assert(unregister_callback("card_draw", draw_handler_1) == 0);
    assert(unregister_callback("card_death", death_handler) == 0);

    // Test trigger_event after unregister_callback
    printf("Only one event should be triggered after this point.\n");
    trigger_event("card_draw", &drawn_card);
    trigger_event("card_death", &slain_card, &slayer_card);

    // Test destroy_event
    destroy_event("card_draw");
    destroy_event("card_death");

    printf("All tests passed.\n");
    return 0;
}
