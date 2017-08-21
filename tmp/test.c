
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include "math.h"

#include <stdbool.h>
#include "color.h"


/*************************
*		wrong cases
*************************/
//#define w_01	//wrong case NO.01		strcpy before malloc
//#define w_02	//wrong case NO.02		strncpy pointer cross-border


/*************************
*		demo
*************************/
//#define d_01	//show the usage of strcpy and strncpy
//#define d_02	//find and return the substring



#define test

void print_trace()
{
    my_trace(BRIGHT, GREEN, BLACK, "good\n");
}


#ifdef test
int main(void)
{
	const char *str = "htt p://dd. ae";
	const char *sub = "d. ae";
	char *ret;

	ret = my_strstr(str, sub);

	printf("%s\n", ret);

	
	return 0;
}

#elif defined d_03

int main(void)
{
	number |= 1 << x;			//set bit x
	number &= ~(1 << x);		//clear bit x
	number ^= 1 << x;			//toggling bit x   (XOR)
	bit = (number >> x) & 1;	//checking a bit -- this will put the value of bit x into the variable bit.
	number ^= (-x ^ number) & (1 << n);		//bit n will be set if x is 1, and cleared if x is 0.
	
	return 0;
}

#elif defined d_02

char *
mystrstr5(const char *s1, const char *s2)
{
    const char   *p  = s1;
    const size_t len = strlen(s2);

    for ( ; (p = strchr(p, *s2)) != 0; p++)
    {
        if (strncmp(p, s2, len) == 0)
        {
            return (char *)p;
        }
    }
    return (char *)(0);
}

char *mystrstr4(string, substring)
register char *string;          /* String to search. */
char *substring;                /* Substring to try to find in string. */
{
    register char *a, *b;

    /* First scan quickly through the two strings looking for a
     * single-character match.  When it's found, then compare the
     * rest of the substring.
     */

    b = substring;
    if (*b == 0)
    {
        return string;
    }
    for ( ; *string != 0; string += 1)
    {
        if (*string != *b)
        {
            continue;
        }
        a = string;
        while (1)
        {
            if (*b == 0)
            {
                return string;
            }
            if (*a++ != *b++)
            {
                break;
            }
        }
        b = substring;
    }
    return NULL;
}

char *strstr_6(char *str, char *substr)
{
    while (*str)
    {
        char *Begin   = str;
        char *pattern = substr;

        // If first character of sub string match, check for whole string
        while (*str && *pattern && *str == *pattern)
        {
            str++;
            pattern++;
        }
        // If complete sub string match, return starting address
        if (!*pattern)
        {
            return Begin;
        }

        str = Begin + 1;                // Increament main string
    }
	
    char *ret = "(null)";
    return ret;
}

char *my_strstr1(const char *haystack, const char *needle)
{
    assert(haystack && needle);

    const char *p_h = haystack;
    const char *p_n = needle;

    int        Len_h = strlen(haystack);
    int        Len_n = strlen(needle);
    int        i = 0, j = 0;

    for (i = 0; i < (Len_h - Len_n); i++)
    {
        int tmp = i;

        for (j = 0; j < Len_n; j++)
        {
            if (*(p_h + tmp++) != *(p_n + j))
            {
                break;
            }
        }
        if (j == strlen(needle))
        {
            return (char *)(p_h + i);
        }
    }

    char *p = "(null)";

    return p;
}

char *my_strstr2(const char *haystack, const char *needle)
{
    assert(haystack && needle);

    const char *p_h, *p_n;

    for ( ; *haystack != '\0'; haystack++)
    {
        p_h = haystack;

        for (p_n = needle ; *p_n != '\0'; p_n++)
        {
			printf("p_h = %s\tp_n = %s\n", p_h, p_n);
			
            if (*p_h++ != *p_n)
            {
                break;
            }
        }

        if (*p_n == '\0')
        {
            return (char *)haystack;
        }
    }
    char *ret = "(null)";

    return ret;
}

char *my_strstr3(const char *s1, const char *s2)
{
	assert(s1 && s2);
	
	const char *str = s1;
	
	for(; strchr(str, *s2) != NULL; str++)
	{
		if(strncmp(str, s2, strlen(s2)) == 0)
		{
			return (char *)str;
		}
	}

	char *p = "(null)";
	return p;
}

int main(void)
{
#if 1
//step1: use pointer string

/*	char *p1 = (char *)malloc(100);
 *      strcpy(p1, "happydayto dance");
 *
 *      char *p2 = (char *)malloc(100);
 *      strcpy(p2, "day");
 */
    char *p1 = "happydayt odance";
    char *p2 = "appdy";

    char *x = my_strstr(p1, p2);
//	char *null_byte = NULL;//'\0';//(char *)(NULL);

//	char *null_byte = "(null)";//(char *)malloc(100);
//	strcpy(null_byte, "\0");

    printf("%s\n", x);
#else
//step2: use array[]



    const char haystack[20] = "TutorialsPoint";
    const char needle[10]   = "Poddint";
    char       *ret;

    ret = strstr(haystack, needle);

    printf("The substring is: %s\n", ret);
#endif

    return 0;
}

#elif defined w_01                                      // strcpy string, before malloc
int main(void)
{
    char *p1 = "happy";

    strcpy(p1, "showmethe");                    //wrong	"happy" in static/initialized zone, it cannot be changed!
    printf("%s\n", p1);

    char text[] = "This is a list of lists";            //right
    strcpy(text, "good");
    printf("%s\n", text);

    return 0;
}

#elif defined w_02                                      // strncpy, pointer cross-border
int main(void)
{
    char *str = (char *)malloc(100);

    assert(str);

    strcpy(str, "showmethe");
    printf("%s\n", str);

    strcpy(str, "ab");
    printf("%s\n", str);

    strncpy(str, "NMK", 3);                     //wrong
    printf("%s\n", str);
}

#elif defined d_01                                      //show strcpy, strncpy, strstr
int main(void)
{
    char *p1 = (char *)malloc(100);

    assert(p1);

    strcpy(p1, "showmethe");                    //strcpy
    printf("%s\n", p1);
    strcpy(p1, "dd");
    printf("%s\n", p1);


    strncpy(p1, "NMk", 2);                      //strncpy
    printf("%s\n", p1);

    strncpy(p1, "NMk", 3);                      //wrong code
    printf("%s\n", p1);

    char *p2   = "gooday";                      //strstr
    char *find = "da";
    char *pos  = NULL;
    pos = strstr(p2, find);
    printf("%s\n", pos);

    return 0;
}

#endif
