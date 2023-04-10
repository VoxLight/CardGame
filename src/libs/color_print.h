#ifndef COLOR_PRINT_H
#define COLOR_PRINT_H


#ifdef _WIN32
    #define COLOR_PRINT_BLACK 0
    #define COLOR_PRINT_WHITE 7
    #define COLOR_PRINT_BLUE 9
    #define COLOR_PRINT_GREEN 10
    #define COLOR_PRINT_CYAN 11
    #define COLOR_PRINT_RED 12
    #define COLOR_PRINT_MAGENTA 13
    #define COLOR_PRINT_YELLOW 14
#else
    #define COLOR_PRINT_WHITE 0
    #define COLOR_PRINT_RED 31
    #define COLOR_PRINT_GREEN 32
    #define COLOR_PRINT_YELLOW 33
    #define COLOR_PRINT_BLUE 34
    #define COLOR_PRINT_MAGENTA 35
    #define COLOR_PRINT_CYAN 36
#endif


void set_text_color(int color);
void reset_text_color();
void print_colored(int color, const char *format, ...);

#endif // COLOR_PRINT_H