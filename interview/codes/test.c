
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <limits.h>


//hackerRank: permutation

int next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/
    
    static int k = 0;

    if(n == 1)
    {
        return 0;
    }
    
    /* ab  cd  ef
       ab  ef  cd
       cd  ab  ef
       cd  ef  ab
       ef  ab  cd
       ef  cd  ab
    */
    /*
        ab ab bc
        ab bc ab
        ab ab bc
        ab bc ab
        bc ab ab
        bc ab ab
    */
    /*
        ab bc ab
        ab ab bc
        bc ab ab
        bc ab ab
        ab ab bc
        ab bc ab
    */
    /*1. calculate how many elements are different, and delete the duplicates
      2. calculate the factorial
      3. calculate the permutation:
            p = n! / ((n - m)!)
    */

    int i, j;
    char *str[] = s
    if(k == 0) //first time to enter, then set s.
    {
        //list s
        for(i = 0; i < n - 1; i++)
        {

        }
    }
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(strcmp(s[i], s[j]) == 0)
            {
                while(j + 1 < n)
                {
                    s[j] = s[j + 1];
                    j++;
                }
                i--;
                n--;
            }
        }
    }



}


int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));

	for (int i = 0; i < n; i++)
		free(s[i]);

	free(s);

	return 0;
}