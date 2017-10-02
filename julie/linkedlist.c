/***
1.Basic operations on single linked list
1.1 Create a single linked list
1.2 Traverse a single linked list
1.3 Find a node in a single linked list
1.4 Insert a new node in a given single linked list
1.5 Delete a node in a given single linked list
***/
union errorCode
{
  retError=-1,
  retOk
}

typedef struct linkedList
{
	int dataField;
	struct linkedlist *next;
};

/*1.1 Create a single linked list */
struct *CreateLinkedList(void)
{
    int i;
    struct linkedList *pTmp = NULL;
    struct linkedList *pHead =NULL;
    for(i =0;i < 5;i++)
    {
        pTmp = malloc(sizeof(struct linkedList));
        pTmp->dataField = i;
	if(i == 0)
        {
	    pHead = pTmp;
	}
	else
        {
       	    pHead->next = pTmp;
            pHead = pTmp;
        }
    }
    return pHead;
}

/*1.2 Traverse a single linked list*/
errorCode *TraverseLinkedList(struct linkedList *pHead)
{
    errorCode returnVal=retOk;
    struct linkedList *p;

    if(pHead == NULL)
    {
        return retError;
    }
    p = pHead;

    while(p != NULL)
    {
	if(p->next != NULL)
        {
            printf("%d->",p->dataField);
        }
        else
        {
            printf("%d",p->dataField);
        }
    }
    return retOk;
}


/* 1.3 Find a node in a single linked list */
struct linkedList *FindNode(struct linkedList *pHead, int nodeData)
{
    struct linkedList *pTmp;

    if(pHead == NULL)
    {
        return NULL;
    }
   
    pTmp = pHead;
    while(pTmp != NULL)
    {
        if(pTmp->dataField == nodeData)
        {
            printf("Find the node \n");
            break;
        }
        pTmp = pTmp->next;
    }
    if(pTmp == NULL)
    {
        printf("Have not found the node \n");
        return NULL;
    }
    else
    {
        printf("Find the node, will return the node \n");
        return pTmp;
    }
}

/*1.4 Insert a new node in the end of an given single linked list*/
errorCode InsertNewNode(struct linkedList *pHead, int nodeVal)
{
    if(pHead == NULL)
    {
        
    }
}

int main()
{

//Create a new linked list

}
