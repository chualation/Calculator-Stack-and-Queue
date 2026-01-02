#include "queue.h" //header file

/*
Purpose: This function initializes an empty queue by setting pHead and pTail to NULL

@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue

Returns: void
*/
void initializeLinkedQueue(singlyLinkedQueue *pQueue)
{
    pQueue->pHead = NULL;   //initialize pHead to NULL
    pQueue->pTail = NULL;   //initialize pTail to NULL
}

/*
Purpose:This function checks if the queue is empty.

@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue

Returns: 1 - empty, 0 - not empty
*/
int isEmptyLinkedQueue(const singlyLinkedQueue *pQueue)
{
    if(pQueue->pHead == NULL){
        return 1;
    }else{
        return 0;
    }
}

/*
Purpose: This function creates a new node with given integer data.

@param nNum : The data value for the node.

@Returns: a pointer to the new node
*/
singlyQueueNode *createQueueNode(int nNum)
{
    // allocates memory for the node
    singlyQueueNode *pNewNode = (singlyQueueNode *)malloc(sizeof(singlyQueueNode));

    // check for memory allocation failure
    if(pNewNode == NULL){
        return NULL;
    }

    pNewNode->nData = nNum;     //set nData to nNum
    pNewNode->pNext = NULL;     //the new node doesn't point to any next node

    // returns the new node
    return pNewNode;
}

/*
Purpose: This function adds a new element to the queue.

@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue
@param nNum Integer data to be added.

Returns: void
*/
void enqueueLinkedQueue(singlyLinkedQueue *pQueue, int nNum)
{
    //create a new node
    singlyQueueNode *pNewNode = createQueueNode(nNum);

     //handle memory allocation failure
    if(pNewNode == NULL){
        return;
    }

    // If pQueue is empty
    if(isEmptyLinkedQueue(pQueue)){ 
        pQueue->pHead = pNewNode;   // pHead points to new node
        pQueue->pTail = pNewNode;   // pTail points to new node
    }
    // If pQueue is not empty
    else{ 
        pQueue->pTail->pNext = pNewNode;    //set pTail to new node
        pQueue->pTail = pNewNode;           //move pTail to new node
    }
}

/*
This function removes and returns the front element of the queue.

@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue

@Returns: -1 - empty, int - data of the removed pHead
*/
int dequeueLinkedQueue(singlyLinkedQueue *pQueue)
{
    int nNum;
    //cannot dequeue from an empty queue
    if(isEmptyLinkedQueue(pQueue)){
        return -1;
    }

    singlyQueueNode *pTemp = pQueue->pHead;     //store pTemp to pHead
    nNum = pTemp->nData;                        //place nData to nNum
    pQueue->pHead = pTemp->pNext;               //pHead will be plaaced to next node

    //queue will now be empty
    if(pQueue->pHead == NULL){
        //clear pTail
        pQueue->pTail = NULL;
    }

    //free the removed node
    free(pTemp);

    //return the data
    return nNum;
}

/*
Purpose: This function returns the front element without removing it.

@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue

@Returns: -1 - empty, int - data of pHead
*/
int peekLinkedQueue(singlyLinkedQueue *pQueue)
{
    if(isEmptyLinkedQueue(pQueue)){
        return -1;
    }else{
        return pQueue->pHead->nData;
    }
}

/*
Purpose: This function clears the entire queue by dequeueing all elements.

@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue

Returns: void
*/
void clearLinkedQueue(singlyLinkedQueue *pQueue)
{
    //clear the queue while it has elements
    while(!isEmptyLinkedQueue(pQueue)){
        dequeueLinkedQueue(pQueue);
    }

    pQueue->pHead = NULL;   //pHead is reset
    pQueue->pTail = NULL;   //pTail is reset
}

/*
Purpose: This function displays all elements in the queue from head to tail.

@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue

Returns: void
*/
void displayLinkedQueue(const singlyLinkedQueue *pQueue)
{
    //Start from pHead
    singlyQueueNode *pCurrent = pQueue->pHead;
    while(pCurrent != NULL){
        printf("%d ", pCurrent->nData);     //print the data of each noded
        pCurrent = pCurrent->pNext;         //move to the next node
    }
    printf("\n");
}
