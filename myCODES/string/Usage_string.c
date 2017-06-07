//����ͷҪ����
#include <string.h>
 
������: stpcpy
��  ��: ����һ���ַ�������һ��
��  ��: char *stpcpy(char *destin, char *source);
������:
 
#include <stdio.h>
#include <string.h>
 
int main(void)
{
   char string[10];
   char *str1 = "abcdefghi";
 
   stpcpy(string, str1);
   printf("%s\n", string);
   return 0;
}
 
 
 
 
������: strcat
��  ��: �ַ���ƴ�Ӻ���
��  ��: char *strcat(char *destin, char *source);
������:
 
#include <string.h>
#include <stdio.h>
 
int main(void)
{
   char destination[25];
   char *blank = " ", *c = "C++", *Borland = "Borland";
 
   strcpy(destination, Borland);
   strcat(destination, blank);
   strcat(destination, c);
 
   printf("%s\n", destination);
   return 0;
}
 
 
 
 
������: strchr
��  ��: ��һ�����в��Ҹ����ַ��ĵ�һ��ƥ��֮��\
��  ��: char *strchr(char *str, char c);
������:
 
#include <string.h>
#include <stdio.h>
 
int main(void)
 {
	char string[15];
	char *ptr, c = 'r';
 
	strcpy(string, "This is a string");
	ptr = strchr(string, c);
	if (ptr)
	   printf("The character %c is at position: %d\n", c, ptr-string);
	else
	   printf("The character was not found\n");
	return 0;
 }
 
 
 
 
������: strcmp
��  ��: ���Ƚ�
��  ��: int strcmp(char *str1, char *str2);
��Asic�룬str1>str2������ֵ > 0��������ȣ�����0
������:
 
#include <string.h>
#include <stdio.h>
 
int main(void)
 {
	char *buf1 = "aaa", *buf2 = "bbb", *buf3 = "ccc";
	int ptr;
 
	ptr = strcmp(buf2, buf1);
	if (ptr > 0)
	   printf("buffer 2 is greater than buffer 1\n");
	else
	   printf("buffer 2 is less than buffer 1\n");
 
	ptr = strcmp(buf2, buf3);
	if (ptr > 0)
	   printf("buffer 2 is greater than buffer 3\n");
	else
	   printf("buffer 2 is less than buffer 3\n");
 
	return 0;
 }
 
 
 
 
������: strncmpi
��  ��: ��һ�����е�һ��������һ�����Ƚ�, ���ܴ�Сд
��  ��: int strncmpi(char *str1, char *str2, unsigned maxlen);
������:
 
#include <string.h>
#include <stdio.h>
 
int main(void)
{
   char *buf1 = "BBB", *buf2 = "bbb";
   int ptr;
 
   ptr = strcmpi(buf2, buf1);
 
   if (ptr > 0)
	  printf("buffer 2 is greater than buffer 1\n");
 
   if (ptr < 0)
	  printf("buffer 2 is less than buffer 1\n");
 
   if (ptr == 0)
	  printf("buffer 2 equals buffer 1\n");
 
   return 0;
}
 
 
 
/*
������: strcpy
��  ��: ������
��  ��: char *strcpy(char *str1, char *str2);
������:
*/
#include <stdio.h>
#include <string.h>
 
int main(void)
 {
	char string[10];
	char *str1 = "abcdefghi";
 
	strcpy(string, str1);
	printf("%s\n", string);
	return 0;
 }
 
 
 
 
������: strcspn
��  ��: �ڴ��в��ҵ�һ�������ַ������ݵĶ�
��  ��: int strcspn(char *str1, char *str2);
������:
 
#include <stdio.h>
#include <string.h>
#include <alloc.h>
 
int main(void)
 {
	char *string1 = "1234567890";
	char *string2 = "747DC8";
	int length;
 
	length = strcspn(string1, string2);
	printf("Character where strings intersect is at position %d\n", length);
 
	return 0;
 }
 
 
 
 
������: strdup
��  ��: �����������½���λ�ô�
��  ��: char *strdup(char *str);
������:
 
#include <stdio.h>
#include <string.h>
#include <alloc.h>
 
int main(void)
 {
	char *dup_str, *string = "abcde";
 
	dup_str = strdup(string);
	printf("%s\n", dup_str);
	free(dup_str);
 
	return 0;
 }
 
 
 
 
������: stricmp
��  ��: �Դ�Сд�����з�ʽ�Ƚ�������
��  ��: int stricmp(char *str1, char *str2);
������:
 
#include <string.h>
#include <stdio.h>
 
int main(void)
{
   char *buf1 = "BBB", *buf2 = "bbb";
   int ptr;
 
   ptr = stricmp(buf2, buf1);
 
   if (ptr > 0)
	  printf("buffer 2 is greater than buffer 1\n");
 
   if (ptr < 0)
	  printf("buffer 2 is less than buffer 1\n");
 
   if (ptr == 0)
	  printf("buffer 2 equals buffer 1\n");
 
   return 0;
}
 
 
 
������: strerror
��  ��: ����ָ�������Ϣ�ַ�����ָ��
��  ��: char *strerror(int errnum);
������:
 
#include <stdio.h>
#include <errno.h>
 
int main(void)
{
   char *buffer;
   buffer = strerror(errno);
   printf("Error: %s\n", buffer);
   return 0;
}
 
 
 
 
������: strcmpi
��  ��: ��һ��������һ���Ƚ�, ���ܴ�Сд
��  ��: int strcmpi(char *str1, char *str2);
������:
 
#include <string.h>
#include <stdio.h>
 
int main(void)
{
   char *buf1 = "BBB", *buf2 = "bbb";
   int ptr;
 
   ptr = strcmpi(buf2, buf1);
 
   if (ptr > 0)
	  printf("buffer 2 is greater than buffer 1\n");
 
   if (ptr < 0)
	  printf("buffer 2 is less than buffer 1\n");
 
   if (ptr == 0)
	  printf("buffer 2 equals buffer 1\n");
 
   return 0;
}
 
 
 
 
������: strncmp
��  ��: ���Ƚ�
��  ��: int strncmp(char *str1, char *str2, int maxlen);
������:
 
#include <string.h>
#include <stdio.h>
 
int  main(void)
 
{
   char *buf1 = "aaabbb", *buf2 = "bbbccc", *buf3 = "ccc";
   int ptr;
 
   ptr = strncmp(buf2,buf1,3);
   if (ptr > 0)
	  printf("buffer 2 is greater than buffer 1\n");
   else
	  printf("buffer 2 is less than buffer 1\n");
 
   ptr = strncmp(buf2,buf3,3);
   if (ptr > 0)
	  printf("buffer 2 is greater than buffer 3\n");
   else
	  printf("buffer 2 is less than buffer 3\n");
 
   return(0);
}
 
 
 
������: strncmpi
��  ��: �Ѵ��е�һ��������һ���е�һ���ֱȽ�, ���ܴ�Сд
��  ��: int strncmpi(char *str1, char *str2);
������:
 
#include <string.h>
#include <stdio.h>
 
int main(void)
{
   char *buf1 = "BBBccc", *buf2 = "bbbccc";
   int ptr;
 
   ptr = strncmpi(buf2,buf1,3);
 
   if (ptr > 0)
	  printf("buffer 2 is greater than buffer 1\n");
 
   if (ptr < 0)
	  printf("buffer 2 is less than buffer 1\n");
 
   if (ptr == 0)
	  printf("buffer 2 equals buffer 1\n");
 
   return 0;
}
 
 
 
������: strncpy
��  ��: ������
��  ��: char *strncpy(char *destin, char *source, int maxlen);
������:
 
#include <stdio.h>
#include <string.h>
 
int main(void)
{
   char string[10];
   char *str1 = "abcdefghi";
 
   strncpy(string, str1, 3);
   string[3] = '\0';
   printf("%s\n", string);
   return 0;
}
 
 
 
������: strnicmp
��  ��: ��ע�ش�Сд�رȽ�������
��  ��: int strnicmp(char *str1, char *str2, unsigned maxlen);
������:
 
#include <string.h>
#include <stdio.h>
 
int main(void)
{
   char *buf1 = "BBBccc", *buf2 = "bbbccc";
   int ptr;
 
   ptr = strnicmp(buf2, buf1, 3);
 
   if (ptr > 0)
	  printf("buffer 2 is greater than buffer 1\n");
 
   if (ptr < 0)
	  printf("buffer 2 is less than buffer 1\n");
 
   if (ptr == 0)
	  printf("buffer 2 equals buffer 1\n");
 
   return 0;
}
 
 
 
 
������: strnset
��  ��: ��һ�����е������ַ�����Ϊָ���ַ�
��  ��: char *strnset(char *str, char ch, unsigned n);
������:
 
#include <stdio.h>
#include <string.h>
 
int main(void)
{
   char *string = "abcdefghijklmnopqrstuvwxyz";
   char letter = 'x';
 
   printf("string before strnset: %s\n", string);
   strnset(string, letter, 13);
   printf("string after  strnset: %s\n", string);
 
   return 0;
}
 
 
 
������: strpbrk
��  ��: �ڴ��в��Ҹ����ַ����е��ַ�
��  ��: char *strpbrk(char *str1, char *str2);
������:
 
#include <stdio.h>
#include <string.h>
 
int main(void)
{
   char *string1 = "abcdefghijklmnopqrstuvwxyz";
   char *string2 = "onm";
   char *ptr;
 
   ptr = strpbrk(string1, string2);
 
   if (ptr)
	  printf("strpbrk found first character: %c\n", *ptr);
   else
	  printf("strpbrk didn't find character in set\n");
 
   return 0;
}
 
 
 
 
������: strrchr
��  ��: �ڴ��в���ָ���ַ������һ������
��  ��: char *strrchr(char *str, char c);
������:
 
#include <string.h>
#include <stdio.h>
 
int main(void)
{
   char string[15];
   char *ptr, c = 'r';
 
   strcpy(string, "This is a string");
   ptr = strrchr(string, c);
   if (ptr)
	  printf("The character %c is at position: %d\n", c, ptr-string);
   else
	  printf("The character was not found\n");
   return 0;
}
 
 
 
 
������: strrev
��  ��: ����ת
��  ��: char *strrev(char *str);
������:
 
#include <string.h>
#include <stdio.h>
 
int main(void)
{
   char *forward = "string";
 
   printf("Before strrev(): %s\n", forward);
   strrev(forward);
   printf("After strrev():  %s\n", forward);
   return 0;
}
 
 
������: strset
��  ��: ��һ�����е������ַ�����Ϊָ���ַ�
��  ��: char *strset(char *str, char c);
������:
 
#include <stdio.h>
#include <string.h>
 
int main(void)
{
   char string[10] = "123456789";
   char symbol = 'c';
 
   printf("Before strset(): %s\n", string);
   strset(string, symbol);
   printf("After strset():  %s\n", string);
   return 0;
}
 
 
 
 
������: strspn
��  ��: �ڴ��в���ָ���ַ������Ӽ��ĵ�һ�γ���
��  ��: int strspn(char *str1, char *str2);
������:
 
#include <stdio.h>
#include <string.h>
#include <alloc.h>
 
int main(void)
{
   char *string1 = "1234567890";
   char *string2 = "123DC8";
   int length;
 
   length = strspn(string1, string2);
   printf("Character where strings differ is at position %d\n", length);
   return 0;
}
 
 
 
������: strstr
��  ��: �ڴ��в���ָ���ַ����ĵ�һ�γ���
��  ��: char *strstr(char *str1, char *str2);
������:
 
#include <stdio.h>
#include <string.h>
 
int main(void)
{
   char *str1 = "Borland International", *str2 = "nation", *ptr;
 
   ptr = strstr(str1, str2);
   printf("The substring is: %s\n", ptr);
   return 0;
}
 
 
 
������: strtod
��  ��: ���ַ���ת��Ϊdouble��ֵ
��  ��: double strtod(char *str, char **endptr);
������:
 
#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
   char input[80], *endptr;
   double value;
 
   printf("Enter a floating point number:");
   gets(input);
   value = strtod(input, &endptr);
   printf("The string is %s the number is %lf\n", input, value);
   return 0;
}
 
 
 
 
������: strtok
��  ��: �������ڵڶ�������ָ���ķֽ���ָ����ĵ���
��  ��: char *strtok(char *str1, char *str2);
������:
 
#include <string.h>
#include <stdio.h>
 
int main(void)
{
   char input[16] = "abc,d";
   char *p;
 
   /* strtok places a NULL terminator
   in front of the token, if found */
   p = strtok(input, ",");
   if (p)   printf("%s\n", p);
 
   /* A second call to strtok using a NULL
   as the first parameter returns a pointer
   to the character following the token  */
   p = strtok(NULL, ",");
   if (p)   printf("%s\n", p);
   return 0;
}
 
 
 
 
������: strtol
��  ��: ����ת��Ϊ������
��  ��: long strtol(char *str, char **endptr, int base);
������:
 
#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
   char *string = "87654321", *endptr;
   long lnumber;
 
   /* strtol converts string to long integer  */
   lnumber = strtol(string, &endptr, 10);
   printf("string = %s  long = %ld\n", string, lnumber);
 
   return 0;
}
 
 
������: strupr
��  ��: �����е�Сд��ĸת��Ϊ��д��ĸ
��  ��: char *strupr(char *str);
������:
 
#include <stdio.h>
#include <string.h>
 
int main(void)
{
   char *string = "abcdefghijklmnopqrstuvwxyz", *ptr;
 
   /* converts string to upper case characters */
   ptr = strupr(string);
   printf("%s\n", ptr);
   return 0;
}
 
 
 
 
������: swab
��  ��: �����ֽ�
��  ��: void swab (char *from, char *to, int nbytes);
������:
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
char source[15] = "rFna koBlrna d";
char target[15];
 
int main(void)
{
   swab(source, target, strlen(source));
   printf("This is target: %s\n", target);
   return 0;
}

