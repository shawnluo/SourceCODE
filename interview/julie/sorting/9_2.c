#include <stdio.h>
#include <string.h>

//10:52PM
/*
return value descrption:
-1: Input paramater has error
0: NOT anagram
1: Yes, anagram detected
*/
int Check_Anagram(char *pStr1, char *pStr2)
{
	char *pTmp = NULL;
	int hashMap[256] = {0};

	if((pStr1 == NULL)
	|| (pStr2 == NULL))
	{
		return -1;
	}

	pTmp = pStr1;
	while(*pTmp != '\0')
	{
		hashMap[*pTmp++]++;
	}

	pTmp = pStr2;
	while(*pTmp != '\0')
	{
		if(hashMap[*pTmp] == 0)
		{
			printf("\n Not a anagram \n");
			return 0; //Not a anagram
		}
		else if(hashMap[*pTmp] > 0)
		{
			hashMap[*pTmp--]--;
		}
	}
	return 1; //yes, it is a anagram
}


//Oct 20th, 9:53PM
char **MergeAnagram(char *pStr[], int left_start, int left_end, int right_start, int right_end, char *pTmp[])
{
	char **p1 = NULL;
	char **p2 = NULL;
	char **p3 = NULL;
	char **pCheck = NULL;
	int i = 0;
	
	if((pStr == NULL)
	||(left_start < 0)
	||(left_end < 0)
	||(right_start < 0)
	||(right_end < 0)
	||(pTmp == NULL)
	||(left_start > left_end)
	||(right_start > right_end))
	{
		return NULL;
	}

	p1 = pStr+left_start;
	p2 = pStr+right_start;
	p3 = pTmp;
	pCheck = p1;
	while((p1 <= pStr+left_end) && (p2 < pStr + right_end))
	{
		*p3++ = *pCheck;
		p1 = pCheck+1;
		while(p1 <= pStr+left_end)
		{
			if(Check_Anagram(*pCheck, *p1)) //Find new anagram
			{
			 	*p3++=*p1++;	
			}
			else
			{
				*p1++;
			}
		}
		while(p2 <= pStr+right_end)
		{
			if(Check_Anagram(*pCheck, *p2) == 1) //Find new anagram
			{
				*p3++=*p2++;
			}
			else
			{
				*p2++;
			}
		}
		//find next check point
		p3 = pTmp;
		while(*p1 == *p3)
		{
			p1++;
			p3++;
		}
		pCheck = p1;		
	}
	
	//Copy all strings from pTmp to pStr
	p1 = pStr+left_start;
	p2 = pTmp+left_start;
	while(p1 <=pStr+right_end)
	{
		*p1++ = *p2++;
	}
	return pStr;
}


#if 0
char **MergeSortAnagram(char *pStr[], int left, int right, char *pTmp[])
{
	int center = 0;
	
	if((pStr == NULL)
	||(left < 0)
	||(right < 0)
	||(pTmp == NULL))
	{
		return NULL;
	}
	if(left < right)
	{
		center=(left + right) / 2;
		MergeSortAnagram(left,center);
		MergeSortAnagram(center+1,right);
		MergeAnagram(pStr,left,center,center+1,right,pTmp);
	}
}
#endif

//To-do
int main(void)
{
	/* test case1: the two sets of string have anagram at the beginning, middle, ending
	str1 = {"abc","aaa","bca","bbb","cba"};
	str2 = {"bca", "ddd","cab","eee","cba"};
	*/

	/*test case2: the two sets of string does NOT have any anagram
	str1 = {"abc","ddd","eee"};
	str2 = "hhh,","mmm","lll"};
	*/

}

