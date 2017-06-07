#include <stdio.h>
#include <string.h> 

int main (int argc, const char * argv[]) 
{ 
    char        firstname[31];
    char        lastname[31];
    char        fullname[63];

	int			te;

/*****************************************************************************************************************************************
	%[^\n]:
		means "get everything that isn't a newline". 
		If you do that, well, the newline is still there since you got everything that wasn't a newline. 
		You need to now do something with that newline, instead of what you seem to be doing which is "ignore it and hope that it goes away".

	*c: 
		the "*" flag means ignore. *c means ignore a sing character. 
		In the context of your scanf line, that %c will be the newline, which is a single character ('\n').

	So if you typed: mk27\n
		(the newline being because of the enter key), and you capture everything up to but not including the newline with %[^\n], 
		'\n' is left in the buffer. %*c captures one more character and throws it away; because of the context, 
		in this case that character would have to be the newline (get it?).

	Never use fflush(stdin) -- it is not defined by the C standard
	
	http://cboard.cprogramming.com/c-programming/118509-beginner-question-problem-scanf-strings-help.html
*****************************************************************************************************************************************/

    printf( "What is your FIRST name: " );
    scanf( "%[^\n]%*c", firstname );
     
    printf( "What is your LAST name: " );
    scanf( "%[^\n]%*c", lastname );

    printf( "What: " );
	scanf("%d", &te);
	
    strcpy( fullname, firstname );
    strcat( fullname, " " );
    strcat( fullname, lastname );
     
    printf( "Your FULL name is %s and it is %d long.\n", fullname, strlen(fullname) );
           
    return 0;
}
