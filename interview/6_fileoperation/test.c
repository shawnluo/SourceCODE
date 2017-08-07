#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int modify(FILE *fp);
int main()
{
    FILE *fp;

	fp = fopen("t.txt", "r+");
    if (fp == NULL)		
    {
        printf("there is no such file");
        return -1;
    }
    find(fp);
    modify(fp);
    fclose(fp);
    return 0;
}

int find(FILE *fp)
{
    char *t;
    char *idata;
    char *namebuf, *buf2, *addr, *tempbuf;
    char *searchname;
    char *tsearchname, *tnamebuf;
    long count;
    long offsize;

    offsize = 0;
    fseek(fp, 0, SEEK_SET);
    searchname = (unsigned char *)malloc(1024);
    idata      = (unsigned char *)malloc(1024);



    tsearchname = (unsigned char *)malloc(1024);
    tsearchname = searchname;
    while ((*searchname = (unsigned char)fgetc(stdin)) != ':')
    {
        searchname++;
		fgetc(stdin);
    }



    namebuf  = (unsigned char *)malloc(1024);
    tempbuf  = (unsigned char *)malloc(1024);
    tnamebuf = (unsigned char *)malloc(1024);
    namebuf  = tnamebuf;
    while ((t = fgets(tempbuf, 1024, fp)) != NULL)
    {
        fseek(fp, offsize, SEEK_SET);

        while ((*tnamebuf = (unsigned char)fgetc(fp)) != ':')
        {
            tnamebuf++;
            printf("the number is:%s\n", namebuf);
        }

        printf("namebuf:%s\nsearchname:%s\n", namebuf, tsearchname);
        int a = 0;

        if ((a = strcmp(namebuf, tsearchname)) == 0)
        {
            break;
        }

        printf("strcmp is:%d\n", a);

        tnamebuf = namebuf;
        fgets(tempbuf, 1024, fp);
        offsize = ftell(fp);
        printf("%s\n", tempbuf);
    }
    if (t == NULL)
    {
        printf("can't find the number\n");
        return 1;
    }
    else
    {
        printf("the number %s is found\n", namebuf);
        printf("end here\n");
    }
    printf("enter your data **:**\n");

    printf("yeye\n");
    return 0;
}

int modify(FILE *fp)
{
    char *pointbuftemp;
    char *buf, *buf2, *buftemp;
    int  rest;
    long current, next, nextnext, departure;

    buf     = (unsigned char *)malloc(1024);
    buftemp = (unsigned char *)malloc(1024);
    buf2    = buf;
    current = ftell(fp);
    rest    = 1024;
    fgets(buf, rest, fp);
    next      = ftell(fp);
    departure = 0;
    while (fgets(buf, rest, fp) != NULL)
    {
        nextnext  = ftell(fp);
        departure = nextnext - next;
        next      = ftell(fp);
        rest     -= departure;
        buf      += departure;
    }
    fseek(fp, current, SEEK_SET);
    fgets(buftemp, 1024, stdin);
    fputs(buftemp, fp);
    fputs(buf2, fp);
    printf("fflush?\n");
    return 0;
}
