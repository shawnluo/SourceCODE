//Linux C 主线程与子线程参数传递

#include <stdio.h>   
#include <pthread.h>   
  
void* fun(void* arg)  
{  
   
   
 printf("======[%d]====\n",(int)arg);    
 pthread_exit((void*)22);  
}  
  
int main(void)  
{  
  
 pthread_t tid;   
  
 pthread_create(&tid,NULL,fun,(void*)99);    //你没注意的东东   
 void *val;  
 pthread_join(tid,&val);  
 printf("------[%d]-----\n",(int)val);  
  
  
 return 0;  
}  
第二种传结构体    

#include <stdio.h>   
#include <pthread.h>   
#include <stdlib.h>   
  
typedef struct   
{  
    int a;  
    float b;  
      
}*LYp,LY;  
  
LYp sheep;  
float f=0;  
void* fun(void* arg)  
{  
    LYp p=(LYp)arg;  
    printf("===[%d]===[%f]====\n",p->a,p->b);  
    f=1.234;          
    pthread_exit(&f);  
}  
  
int main(void)  
{  
    sheep=malloc(sizeof(LY));  
    sheep->a=100;  
    sheep->b=3.33;  
    pthread_t tid;    
  
    pthread_create(&tid,NULL,fun,sheep);  
    void *val;  
    pthread_join(tid,&val);  
    printf("------[%lf]-----\n",*((float*)val));  
  
    free(sheep);  
  
  
    return 0;  
}  

