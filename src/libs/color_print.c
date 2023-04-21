#include <stdio.h>
#include <stdarg.h>

#include "color_print.h"

#ifdef _WIN32
#include <windows.h>
void set_text_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

#else
void set_text_color(int color) {
    printf("\033[%dm", color);
}
#endif

void reset_text_color() {
    set_text_color(COLOR_PRINT_WHITE);
}

void print_colored(int color, const char *format, ...) {
    set_text_color(color);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    reset_text_color();
}