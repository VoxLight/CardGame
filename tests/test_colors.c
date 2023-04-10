#include <stdio.h>
#include <stdarg.h>

#include "color_print.h"

void test_color_print_red() {
    print_colored(COLOR_PRINT_RED, "red\n");
}

void test_color_print_green() {
    print_colored(COLOR_PRINT_GREEN, "green\n");
}

void test_color_print_yellow() {
    print_colored(COLOR_PRINT_YELLOW, "yellow\n");
}

void test_color_print_blue() {
    print_colored(COLOR_PRINT_BLUE, "blue\n");
}

void test_color_print_magenta() {
    print_colored(COLOR_PRINT_MAGENTA, "magenta\n");
}

void test_color_print_cyan() {
    print_colored(COLOR_PRINT_CYAN, "cyan\n");
}

void test_color_print_white() {
    print_colored(COLOR_PRINT_WHITE, "white\n");
}

void test_color_print_default() {
    printf("This is default\n");
}


int main(){
    test_color_print_red();
    test_color_print_green();
    test_color_print_yellow();
    test_color_print_white();
    test_color_print_blue();
    test_color_print_magenta();
    test_color_print_cyan();
    test_color_print_default();
    puts("All Tests Passed.");
}
