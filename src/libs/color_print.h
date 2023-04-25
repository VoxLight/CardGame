/**
 * @file color_print.h
 * @brief This header file contains the declarations of functions and macros for colored console output.
 */

#ifndef COLOR_PRINT_H
#define COLOR_PRINT_H

// Determines if we are running on Windows or Linux/Unix
// and sets the color pallette to the specific one for the OS.
#ifdef _WIN32
    #define COLOR_PRINT_BLACK 0 /**< The color code for black text on Windows */
    #define COLOR_PRINT_WHITE 7 /**< The color code for white text on Windows */
    #define COLOR_PRINT_BLUE 9 /**< The color code for blue text on Windows */
    #define COLOR_PRINT_GREEN 10 /**< The color code for green text on Windows */
    #define COLOR_PRINT_CYAN 11 /**< The color code for cyan text on Windows */
    #define COLOR_PRINT_RED 12 /**< The color code for red text on Windows */
    #define COLOR_PRINT_MAGENTA 13 /**< The color code for magenta text on Windows */
    #define COLOR_PRINT_YELLOW 14 /**< The color code for yellow text on Windows */
#else
    #define COLOR_PRINT_WHITE 0 /**< The color code for white text on Unix-like systems */
    #define COLOR_PRINT_RED 31 /**< The color code for red text on Unix-like systems */
    #define COLOR_PRINT_GREEN 32 /**< The color code for green text on Unix-like systems */
    #define COLOR_PRINT_YELLOW 33 /**< The color code for yellow text on Unix-like systems */
    #define COLOR_PRINT_BLUE 34 /**< The color code for blue text on Unix-like systems */
    #define COLOR_PRINT_MAGENTA 35 /**< The color code for magenta text on Unix-like systems */
    #define COLOR_PRINT_CYAN 36 /**< The color code for cyan text on Unix-like systems */
#endif

/**
 * @brief Sets the console text color to the specified color.
 * 
 * @param color The color code to use.
 */
void set_text_color(int color);

/**
 * @brief Resets the console text color to the default color.
 */
void reset_text_color();

/**
 * @brief Prints the specified string to the console with the specified color.
 * 
 * @param color The color code to use.
 * @param format The format string to print.
 * @param ... The arguments to the format string.
 */
void print_colored(int color, const char *format, ...);

#endif // COLOR_PRINT_H
