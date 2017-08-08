
#if 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#include "color.h"

#if 0
//attr
#define RESET        0
#define BRIGHT       1
#define DIM          2
#define UNDERLINE    4
#define BLINK        5
#define REVERSE      7
#define HIDDEN       8

//fg/bg
#define BLACK        0
#define RED          1
#define GREEN        2
#define YELLOW       3
#define BLUE         4
#define MAGENTA      5
#define CYAN         6
#define WHITE        7
#endif

void textcolor(int attr, int fg, int bg)
{
    char command[13];

    /* Command is the control command to the terminal */
    sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
    printf("%s", command);
}

void my_trace(int attr, int fg, int bg, const char *cmd, ...)
{
    textcolor(attr, fg, bg);
//    printf("%s %s ", __DATE__, __TIME__);
//    printf("[%s %s %d]\t", __FILE__, __func__, __LINE__);

    va_list args;
    va_start(args, cmd);
    vprintf(cmd, args);
    va_end(args);
    textcolor(RESET, WHITE, BLACK);
}


/*
 #define PRINT(str, fmt, arg...) \
 *      do { \
 *              sprintf(str, "%s " fmt, "" ); \
 *              }while(0)
 */

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


//===================================


#else
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>


#define log_to_string1(str, fmt, arg ...)           \
    do {                                            \
        sprintf(str, "%s: " fmt, "myprog", ## arg); \
    } while (0)

#define log_to_string2(str, fmt, arg ...)           \
    ({                                              \
        sprintf(str, "%s: " fmt, "myprog", ## arg); \
    })

void my_trace(const char *cmd, ...)
{
    printf("%s %s ", __DATE__, __TIME__);
    va_list args;
    va_start(args, cmd);
    vprintf(cmd, args);
    va_end(args);
}


int main()
{
    char buf[1000];
    int  n = 0;

    log_to_string1(buf, "%s\n", "No assignment, OK");

    log_to_string1(buf + n, "%s\n", "NOT OK: gcc: error: expected expression before 'do'");

    n += log_to_string2(buf + n, "%s\n", "This fixes it");
    n += log_to_string2(buf + n, "%s\n", "Assignment worked!");
//        printf("%s", buf);

    char *str = "show me the money!";

    my_trace("%s\n", str);
    return 0;
}

#endif
