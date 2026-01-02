#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

/*
Purpose: A struct to represent the nodes in a singl linked stack

@ nData : to store node
@ pNext: a pointer to the next node
*/
typedef struct singlyStackNode{
    int nData;
    struct singlyStackNode *pNext;
}singlyStackNode;

/*
Purpose: A struct that represents the entire stack

@ pTop : a pointer that points to the top node of the stack
*/
typedef struct{
    singlyStackNode *pTop;
}singlyLinkedStack;

//Alias
typedef struct singlyStackNode singlyStackType;

// Function Prototypes for stack.c
void initializeLinkedStack(singlyLinkedStack *pStack);
int emptyLinkedStack(singlyLinkedStack *pStack);
singlyStackType *add_node(singlyStackType *pStack, int nNum);
void pushLinkedStack(singlyLinkedStack *pStack, int nNum);
int popLinkedStack(singlyLinkedStack *pStack);
int peekLinkedStack(singlyLinkedStack *pStack);
void clearLinkedStack(singlyLinkedStack *pStack);

#endif
