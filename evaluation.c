#include "evaluation.h"

/*
Purpose: This function counts the number of nodes in the queue

@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue

Returns: The number of tokens in the queue
*/
int countNodes(singlyLinkedQueue *pQueue) 
{
    int nCtr = 0;

    singlyQueueNode *pCurr = pQueue->pHead;

    while(pCurr != NULL){
        nCtr++;
        pCurr = pCurr->pNext;
    }
    return nCtr;
}

/*
Purpose: This function is a helper function to compute for an exponential expression

@param nBase : assignment of the base number
@param nExponent :  assignment of the exponent number to be used as the amount of times to multiply the base

Returns: nBase raised to nExponent
*/
int exponentHelper(int nBase, int nExponent)
{
    int nPower = 1;

    for(int i = 0; i < nExponent; i++){
        nPower *= nBase;
    }

    return nPower;
}

/*
Purpose: This function will compute the operation between two opertaors

@param nFirst : assigned of  the first operator
@param nSecond : assignment of the second operator
@param nOP : the operator to be used

Returns: computation bsed on the given 
*/
int operatorHelper(int nFirst, int nSecond, int nOP)
{
    switch(nOP){
        case ADDITION:       
            return nFirst + nSecond;
        case SUBTRACTION:    
            return nFirst - nSecond;
        case MULTIPLICATION: 
            return nFirst * nSecond;
        case DIVISION:       
            return nFirst / nSecond;
        case MODULO:         
            return nFirst % nSecond;
        case EXPONENTIAL:
            return exponentHelper(nFirst, nSecond);
        case GREATER:        
            return nFirst > nSecond;
        case LESS:           
            return nFirst < nSecond;
        case GREATER_EQUAL:  
            return nFirst >= nSecond;
        case LESS_EQUAL:     
            return nFirst <= nSecond;
        case EQUAL:          
            return nFirst == nSecond;
        case NOT_EQUAL:      
            return nFirst != nSecond;
        case AND:            
            return nFirst && nSecond;
        case OR:            
            return nFirst || nSecond;
        default:             
            return 0; 
    }   
}

/*
Purpose: This function will return the symbol of the given operator

@param nOP : the operator to be used

Returns: symbol of the opertor
*/
const char *symbolHelper(int nOP)
{
    switch(nOP){
        case ADDITION:       
            return "+";
        case SUBTRACTION:    
            return "-";
        case MULTIPLICATION: 
            return "*";
        case DIVISION:       
            return "/";
        case MODULO:         
            return "%";
        case EXPONENTIAL:    
            return "^";
        case GREATER:        
            return ">";
        case LESS:           
            return "<";
        case GREATER_EQUAL:  
            return ">=";
        case LESS_EQUAL:     
            return "<=";
        case EQUAL:          
            return "==";
        case NOT_EQUAL:      
            return "!=";
        case AND:            
            return "&&";
        case OR:             
            return "||";
        case NOT:            
            return "!";
        default:             
            return "?"; 
    }
}

/*
Purpose: This function will evaluate the postfix expression stored in the queue

@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue
@param pError : a pointer to an integer flag that will set to 1 when a division by zero is encountered

Returns: the result of the evaluated postfix expression
*/
int evaluatePostfix(singlyLinkedQueue *pQueue, int *pError) {
    
    int nResult;            //stores the result of the evaluation
    int nFirst, nSecond;    //stores the operators
    
    singlyLinkedStack nStack;                  //initialize the stack for operators
    initializeLinkedStack(&nStack);            //initialize the stack to be empty before called
    singlyQueueNode *pCurr = pQueue->pHead;    //initialized to traverse the queue

    //traverse the queue until end
    while(pCurr != NULL){
        //if the current node is non-negative
        if (pCurr->nData >= 0) {
            pushLinkedStack(&nStack, pCurr->nData);     //push the operator onto the stack
        }else{
            //if the current node is '!' (NOT) / unary operator
            if(pCurr->nData == NOT){
                nFirst = popLinkedStack(&nStack);       //pop one operator from the stack
                pushLinkedStack(&nStack, !nFirst);      //place '!' (NOT) and push the result
            //else, if the current node is a binary operator
            }else{
                nSecond = popLinkedStack(&nStack);      //pop nSecond
                nFirst = popLinkedStack(&nStack);       //pop nFirst
                
                //check for any division by zero error
                if((pCurr->nData == DIVISION || pCurr->nData == MODULO) && nSecond == 0){
                    *pError = 1;                //set the error flag to 1
                    clearLinkedStack(&nStack);  //clear the stack 
                    return 0;                   
                }
                nResult = operatorHelper(nFirst, nSecond, pCurr->nData);    //computes the result of the operation
                pushLinkedStack(&nStack, nResult);                          //push the result back onto the stack
            }
        }
        pCurr = pCurr->pNext;   //move to the next node
    }
    nResult = popLinkedStack(&nStack);  //pop the last value in the stack
    clearLinkedStack(&nStack);          //clear the stack

    return nResult;
}

/*
Purpose: This function will print the postfix expression stored in the queue

@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue

Returns: void
*/
void printQueue(singlyLinkedQueue *pQueue) 
{
    singlyQueueNode *pCurr = pQueue->pHead;

    //traverse the queue until end
    while(pCurr != NULL){
        //check if the current node is non negative
        if(pCurr->nData >= 0){
            printf("%d ", pCurr->nData);                 //print the value
        }else{
            printf("%s ", symbolHelper(pCurr->nData));  //print the symbol
        }
        pCurr = pCurr->pNext;                           //move to the next node
    }
    printf("\n");
}
