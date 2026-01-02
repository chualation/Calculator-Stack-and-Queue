#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

/* 
Purpose: Represents a node in the queue

@ nData : to store node
@ pNext : a pointer to the next node
*/
typedef struct singlyQueueNode{
    int nData;
    struct singlyQueueNode *pNext;
} singlyQueueNode;

/* 
Purpose: represents the entire queue 

@ pHead : pointer to the first node
@ pTail : pointer to the last node
*/
typedef struct{
    singlyQueueNode *pHead; 
    singlyQueueNode *pTail; 
} singlyLinkedQueue;

// Function Protypes for queue.c
void initializeLinkedQueue(singlyLinkedQueue *pQueue);
int isEmptyLinkedQueue(const singlyLinkedQueue *pQueue);
singlyQueueNode *createQueueNode(int nNum);
void enqueueLinkedQueue(singlyLinkedQueue *pQueue, int nNum);
int dequeueLinkedQueue(singlyLinkedQueue *pQueue);
int peekLinkedQueue(singlyLinkedQueue *pQueue);
void clearLinkedQueue(singlyLinkedQueue *pQueue);
void displayLinkedQueue(const singlyLinkedQueue *pQueue);

#endif 
