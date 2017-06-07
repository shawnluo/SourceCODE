


例子一


//原型：extern char *strchr(char *s,char c);
        
//  用法：#include <string.h>
  
//  功能：查找字符串s中首次出现字符c的位置
  
//  说明：返回首次出现c的位置的指针，如果s中不存在c则返回NULL。
  
//  举例：


      // strchr.c
      
      #include <syslib.h>
      #include <string.h>

      main()
      {
        char *s="Golden Global View";
        char *p;
        
        clrscr();
        
        p = strchr(s,'V');
        if(p)
          printf("%s",p);
        else
          printf("Not Found!");

        getchar();
        return 0;
      }





例子二

//strchr()函数的作用是：返回一个字符串在另一个字符串中首次出现的位置到后者末尾的子字符串.

#include <stdio.h> 
#include <stdlib.h> 
char *GetStr(char *Buffer,int n,char Split,char *Target);
int main(int argc, char *argv[]) 
{ 
    int i,j,k;
    char split;
    char buffer[512];
    char target[512];
    char tmp_buff[128];
    char tmp_targ[128];
    char tmp_swap[128];
    FILE *pf;

    split = ',';
    i=0;j=0;k=0;
    
    pf = fopen("1.txt","r");    
    
    while ( NULL!=(fgets(buffer,sizeof(buffer),pf)) ) 
    {
        j=0;
        memset(tmp_buff,0,sizeof(tmp_buff));

        if((buffer[strlen(buffer)-1]==0x0a)||(buffer[strlen(buffer)-1]==0x0d))
            strncpy(tmp_buff,buffer,strlen(buffer)-1);
        else
            strcpy(tmp_buff,buffer);

        for(i=0;i<strlen(tmp_buff);i++)
            if(tmp_buff[i]==split)
                j++;

        for(i=0;i<j+1;i++)
        {   
            memset(target,0,sizeof(target));
            GetStr(tmp_buff,i,split,target);
            /*strrev(target);*/
            for(k=strlen(target)-1;k>=0;k--)
                printf("%c",target[k]);
            if(i!=j)
                printf("%c",split);
        }
        printf("\n");
        memset(buffer,0,sizeof(buffer));         
    }   
    fclose(pf);
} 

char *GetStr(char *Buffer,int n,char Split,char *Target)
{
    int i,j=0;
    memset(Target,0,sizeof(Target));
    for(i=0;i<strlen(Buffer);i++)
    {
        if((Buffer[i]!=Split)&&(n==0))
            Target[j++]=Buffer[i];
        if(Buffer[i]==Split)
            n--;
        if((n<0)||(Buffer[i]==0x0d)||(Buffer[i]==0x0a))
            break;
    }   
    return (Target);
}

//因为不知道题目要求倒排之后的要求,
//我就把结果输出到屏幕上了.

//1.txt的内容如下:
//123,abc,asd
//321,abc

//屏幕输出结果:
//321,cba,dsa
//123,cba

