#ifndef EVALUATION_H
#define EVALUATION_H

#include <stdio.h>
#include "infix-to-postfix.h" //infix-to-postfix hedaer file
#include "queue.h"            //queue header file

int countNodes(singlyLinkedQueue *pQueue);
int exponentHelper(int nBase, int nExponent);
int operatorHelper(int nFirst, int nSecond, int nOP);
const char *symbolHelper(int nOP);
int evaluatePostfix(singlyLinkedQueue *pQueue, int *pError);
void printQueue(singlyLinkedQueue *pQueue);

#endif
