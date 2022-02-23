
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


/*
        1.1. determin if a string has all unque char
*/

/*
    initialize a int arr[128], set to 0
    then go through the string, add 1 to the arr[*str].
    if the arr[*str] = 1, then return
*/
int Is_unique(const char *str)
{
    if(!str)
    {
        printf("str is invalid!\n");
        return -1;
    }

    int arr[128] = {0};
    while(*str != '\0')
    {
        //arr[*str] = 1;
        if(arr[*str] == 0)
        {
            arr[*str] = 1;
        }
        else
        {
            return 1;
        }

        str++;
    }
    return 0;
}

int main()
{
    const char *arr = "showme";

    printf("%d\n", Is_unique(arr));

    return 0;
}



/*
        1.2 reverse a C-Style String
*/

/*
    using char *pStart to point to the string start,
    char *pEnd to point to the string end
    save pStart to tmp;
    while loop, (condition : pStart < pEnd)
        swap pStart and pEnd, then pStar++, pEnd--
*/
int reverse_str(char *str)
{
    if(!str)
    {
        printf("invalid string!\n");
        return -1;
    }

    char *pStar = str;
    char *pEnd = str + strlen(str) - 1;
    char tmp;

    while(pStar < pEnd)
    {
        tmp = *pStar;
        *pStar = *pEnd;
        *pEnd = tmp;
        pStar++;
        pEnd--;
    }

    return 0;
}

int main()
{
    char arr[] = "showme";
    if(reverse_str(arr) == -1)
    {
        return -1;
    }

    printf("%s\n", arr);

    return 0;
}


/*
        1.3 remove the duplicat char in a string without using any additional buffer
            can NOT use extra copy of the array
*/


/*
    1. move str[n + 1] to str[n], untile str[n + 1] == '\0'
    2. 
*/
int move_str(char *str)
{
    if(!str)
    {
        printf("str is empty!\n");
        return -1;
    }

    while(*str != '\0')     // if *str is '\0', then just copy it as an string end char
    {
        *str = *(str + 1);
        str++;
    }

    return 0;
}


/*
    str: "abcaaabc" --> "abc"
    1. first while loop ( condition: str != '\0'):
        goes through from the beginning of str, 
    2. second  loop:
        *p, goes through from the str + 1.
        if *str == *p, then move the flowing char step forward
        add '\0' to the end of str
*/
int remove_dup_str(char *str)
{
    if(!str)
    {
        printf("invalid string!\n");
        return -1;
    }

    char *p = str;

    //abcabaaa
    while(*str != '\0')
    {
        //printf("%c\n", *(str + 1));
        for(p = str + 1; *p != '\0'; p++)
        {
            if(*str == *p)
            {
                move_str(p); // move *(P + 1) to *p, until the end of str
                p--;            // just in case there are multiple same character like "abccc", so need to recheck it
            }
        }
        str++;
    }

    return 0;
}

int main()
{
    char arr[] = "abcaaabbbaa";
    if(remove_dup_str(arr) == -1)
    {
        return -1;
    }

    printf("%s\n", arr);

    return 0;
}



/*
        1.4 decide if 2 strings are anagrams or not
            "abc"    -   "bac"
*/


/*
    initize a int data1[128], go through the str, increase arr[*str] when meet *str,
    run the same function for another str, generate a data2[128],
    if the data1 equal data2. then they are anagrams
*/
int Is_anagrams(char *str1, char *str2)
{
    if((!str1) || (!str2))
    {
        printf("str is empty!\n");
        return -1;
    }

    int i;
    char data1[128] = {0};
    char data2[128] = {0};

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if(len1 != len2)
        return 1;

    for(i = 0; i < len1; i++)
    {
        //printf("*str1 = %d\n", *str1);
        data1[*str1++]++;
    }

    for(i = 0; i < len2; i++)
    {
        data2[*str2++]++;
    }

    for(i = 0; i < 128; i++)
    {
        if(data1[i] != data2[i])
        {
            //printf("%c, %c\n", data1[i], data2[i]);
            return 2;
        }
    }

    return 0;
}



int main()
{
    char *arr1 = "show me";
    char *arr2 = "me owsh";
    int ret = Is_anagrams(arr1, arr2);

    printf("%d\n", ret);

    return 0;
}



/*
        1.5 write a method to replace all spaces in a string with '%20'
            "a bc"    -   "a%20bc"
*/


/*
    1. go through str, to calculate how many space, num.
    2. inilize a new str_new, size set to (3 - 1) * num + strlen(str)
    3. 2 while loop to copy str to str_new start from tail,
        1). one from str tail, decrease
        2). another from str_new, decrease
        3). if meet space, 
            a. str--
            b. str_new[i] = '0'
            c. str_new[i - 1] = '2'
            d. str_new[i - 2] = '%'
*/
int replace_space(char *str, char *str_new)
{
    if(!str)
    {
        printf("str is empty!\n");
        return -1;
    }

    int len_str = strlen(str);

    int num = 0;    // how many old_ch
    char *p = str;
    while(*p)
    {
        if(*p == ' ')
        {
            num++;
        }
        p++;
    }
    //return num;

    int len_new = len_str + num * (3 - 1); // len "%20" - len ' '
    //char str_new[len_new];

    char *p1 = str + len_str - 1;      // str end
    char *p2 = str_new + len_new - 1;  // new str end

    while(len_str--)
    {
        if(*p1 == ' ')
        {
            *p2 = '0';
            *(p2 - 1) = '2';
            *(p2 - 2) = '%';
            p1--;
            p2 -= 3;
        }
        else
        {
            *p2 = *p1;
            p1--;
            p2--;
        }
    }

    str_new[len_new] = '\0';
    //printf("%s\n", str_new);
}


int main()
{
    char *str = " ";
    char str_new[100] = {};

    int ret = replace_space(str, str_new);

    //printf("%d\n", ret);
    printf("%s\n", str_new);

    return 0;
}


/*
        1.7 write an algorithm such that if an element in an MxN matrix is 0, then set its entire row and column to 0
            1 0 1      -->      0 0 0
            1 1 1               1 0 1
*/


/*
    set arr[][j] and arr[i][] to 0;
*/
void set_newArr(int arr[5][5], int x, int y, int i, int j)
{
    int row, col;

    for(row = 0; row < x; row++)
    {
        arr[row][j] = 1;
    }

    for(col = 0; col < y; col++)
    {
        arr[i][col] = 1;
    }

#if 1
    printf("------ new arr ------\n");
    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            printf("%d, ", arr[i][j]);
        }
        printf("\n");
    }
#endif
}

/*
    1. create a new arr, set all the elements to 0
    2. go through the arr, if find element is 0c then mark the row and column to 1 in the new arr.
    3. compare the 2 arrarys, any elements in the new arr marked as 1, then set it to 0 in the arr. 
*/
int mark_matrix(int arr[5][5], int x, int y)
{
    int newArr[50][15] = {0};
    


    int i, j;
    for(i = 0; i < 50; i++)
    {
        for(j = 0; j < 15; j++)
        {
            memset(newArr[i], 0, j);
        }
    }


    int row, col;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            if(arr[i][j] == 0)
            {
                printf("i = %d, j = %d, x = %d, y = %d\n", i, j, x, y);

                set_newArr(newArr, x, y, i, j);
#if 0
                for(row = 0; row < 5; row++)
                {
                    newArr[row][j] = 1;
                }

                for(col = 0; col < 5; col++)
                {
                    newArr[i][col] = 1;
                }
#endif
            }
        }
    }

    printf("------ new arr 2 ------\n");
    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            printf("%d, ", newArr[i][j]);
        }
        printf("\n");
    }

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            if(newArr[i][j] == 1)
            {
                arr[i][j] = 0;
            }
        }
    }

    printf("------ arr ------\n");
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            printf("%d, ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int main()
{
    int arr[5][5] = {   {1, 0, 1, 1, 1},
                        {1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1},
                        {1, 1, 1, 0, 1},
                        {1, 1, 1, 1, 1}
    };

    int ret = mark_matrix(arr, 5, 5);

    //printf("%d\n", ret);
    //printf("%s\n", str_new);

    return 0;
}




/*
        1.7 write an algorithm such that if an element in an MxN matrix is 0, then set its entire row and column to 0
            1 2 3      -->      7 4 1
            4 5 6               8 5 2
            7 8 9               9 6 3
*/


/*
    step 1. transpose the matrix and then flip it symmetrical swap
    1 2 3           1 4 7
    4 5 6           2 5 8
    7 8 9           3 6 9

    step2. flip the matrix horizontally
    1 4 7           7 4 1
    2 5 8           7 5 2
    3 6 9           9 6 3
*/

#define row 5
#define col 5

void swap(int arr[row][col])
{
    int i, j, tmp;

    for(i = 0; i < row; i++)
    {
        for(j = 0; j <= i; j++)
        {
            tmp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = tmp;
        }
    }

/*
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            printf("%d, ", arr[i][j]);;
        }
        printf("\n");
    }
*/

#if 1
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col / 2; j++)
        {
            tmp = arr[i][j];
            arr[i][j] = arr[i][5 - j - 1];
            arr[i][5 - j - 1] = tmp;
        }
    }

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            printf("%d, ", arr[i][j]);;
        }
        printf("\n");
    }
#endif
}

int main()
{
    int arr[row][col] = {   {1, 2, 3, 4, 5},
                        {6, 7, 8, 9, 10},
                        {11, 12, 13, 14, 15},
                        {16, 17, 18, 19, 20},
                        {21, 22, 23, 24, 25}
    };

    swap(arr);

    //printf("%d\n", ret);
    //printf("%s\n", str_new);

    return 0;
}