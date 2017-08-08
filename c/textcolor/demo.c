#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#include "tc.h"

int main()

{
    int  i    = 55;
    char *str = "show me";

    printf("\x1b[%d;%dmhello world \x1b[0m 47: white 30: black \n", 47, 30);


/*
 *      textcolor(BLINK, RED, BLACK);
 *      printf("In color i = %d\tstr = %s\n", i, str);
 *      textcolor(RESET, WHITE, BLACK);
 */
    my_trace(BLINK, RED, BLACK, "In color i = %d\tstr = %s\n", i, str);
    return 0;
}

