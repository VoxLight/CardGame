#include <stdio.h>

#include "console.h"


int main() {
    const char* test1 = "Hello, world!";
    const char* test2 = " \"\'\p\t  ";

    printf("Test 1 is printable: %s\n", is_printable(test1) ? "true" : "false");
    printf("Test 2 is printable: %s\n", is_printable(test2) ? "true" : "false");

    return 0;
}