void ControlSound(int Input)
{
    int i;
    int data = 0;
    
    int volatile *reg = (int *)0x80000000;
     *reg |= (1<<0x7); //enable the control
     
     for(i = 8;i <=15;i++)
     {
         data |= (Input >> i);
         data <<= 1;
     }
     *reg |= (data << 7);
}

// Volume can be 0 - 255
ControlSound(5,1);
ControlSound(8,1);

#define ENABLE_BIT 0x07
#define VOLUME_START_BIT 0x0
#define VOLUME_END_BIT 0x7
bool ControlSound(int Volume,bool Enable)
{
    int i;
    int data = 0;
    int max = ~0;
    int left = 0;
    int right = 0;
    int mask = 0;
    
    int volatile *reg = (int *)0x80000000;
    *reg |= (1<<0x7); //enable the control
   
    if(Enable == TRUE)
    {
       *reg |= (1 << ENABLE_BIT);
    } 
    else
    {
        *reg &= ~(1 << ENABLE_BIT);
    }
    
    
    //set the volume
    if((Volume >= 0) && (Volumne <= 255))
    {
        #if 0
        for(i = VOLUME_START_BIT;i <= VOLUME_END_BIT;i++)
        {
            data |= (Volume >> i);
            data <<= 1; 
        }
        #endif
        
        data = Volume;
        data <<= 8;
        
        #if 0
        //clear the volume bits in the register first
        left = max - (1 << VOLUME_END_BIT)-1;
        right = (1 << VOLUME_END_BIT)-1;
        mask = left|right;
        #endif
        
        mask = 0;
        mask = (0xff) << 8;
        
        *reg &= ~mask;
        
        //write data into register
        *reg |= data;
        
        return TRUE;
 
    }
    else
    {
        return FALSE;
    }
}


// Volume can be 0 - 255
ControlSound(5,1);
ControlSound(8,1);

int Power(int m,int n)
{
    int ret = 0;
    int result = 0;
    if(n == 1)
    {
        return m;
    }
    else if(n == 0)
    {
        return 1;
    }
    if((n % 2) == 0)
    {
        ret = Power(m,n/2);
        result = ret * ret;
    } 
    else
    {
        ret = Power(m,n/2);
        result = ret * ret * m;
    }
    return result;
}
Power(3,2) // returns 9
Power(3,3) // returns 27



char *ReverseString(char *s)
{
    int len;
    char tmp = 0;
    char *begin = NULL;
    char *end = NULL;
    if(s == NULL)
    {
        return NULL;
    }    
    len = strlen(s);
    begin = s;
    end = s + len -1;
    
    while(begin < end)
    {
        tmp = *begin;
        *begin = *end;
        *end = tmp;
        begin++;
        end--;
    }
    return s;
}


int CountBits(int num)
{
    int i;
    int count = 0;
    
    for(i = 0;i < 32;i++)
    {
        if((num >> i) & 0x01)
        {
            count++;
        }    
    }
    return count;
}

#define CountBits(x) {\
x = 1;
int count = 0;     \
while(x != 0)     \
{
    if(x & 0x01)
    {
        count++;
    }
    x <<= 1;
    printf("count=%d",count);
}



Your function receives 10 numbers one after the other. You need to check whether each number is a palindrome.
Maintain a queue where you need to push the number if it is a palindrome. Disregard the number if it not a palindrome.
Use linked list.

For eg: 12321
    34265
    56765
    36266
    66666
    .....
The queue should have <12321> <56765> <66666>



#define YES 1
#define NO 0
int checkPalindrome(unsigned int number)
{
    int ret = 0, sign = number >> 31;
    int save = number;
      
    //reverse the number
    
    while(number != 0)
    {
        ret = ret * 10 + number % 10;
        number = number / 10;
    }
    
    if(sign != (ret >> 31))
    {
        exit(1);
    }
    
    if(save != ret)
    {
        return NO;
    }
    else
    {
        return YES;
    }
}

int My_Sorting(int array[], int muber)
{
    
}



typedef struct node
{
    int num;
    struct node *next;
} Node, *pNode;

#define LEN sizeof(struct node)

//Node *Create_Linkedlist(int arrary[], int number)
pNode Create_Linkedlist(int arrary[], int number)
{
    pNode pHead = NULL, p = NULL;
    
    while(number--)
    {
        p = (pNode)malloc(LEN);
        p->num = number;
        p->next = pHead;
        phead = p;
    }
    
    return pHead;
}


//1. put all the numbers into a array;
//2. check  the number is palindrome or not one by one.

