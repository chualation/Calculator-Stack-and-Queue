#include "stack.h" //header file

/*
Purpose: This function will initialize the stack

@param pStack : LinkedStack *pStack - a pointer to the stack structure

Returns: void
*/
void initializeLinkedStack(singlyLinkedStack *pStack)
{
    // set pTop to NULL for an empty stack
    pStack->pTop = NULL;
}

/*
Purpose: This function will check if the stack is empty

@param pStack : LinkedStack *pStack - a pointer to the stack structure

Returns: 1 - empty, 0 - not empty
*/
int emptyLinkedStack(singlyLinkedStack *pStack)
{
    if(pStack->pTop == NULL){
        return 1;
    }else{
        return 0;
    }
}

/*
Purpose: This function adds a node to the start of the linked list

@param pStack : LinkedStack *pStack - a pointer to the stack structure
@param nNum : int - to store the new node

Returns: a pointer to the new node
*/
singlyStackType *add_node(singlyStackType *pStack, int nNum)
{
    //creates space for the new node
    singlyStackType *pCur = (singlyStackType*) malloc(sizeof(singlyStackType));

    pCur->nData = nNum;     //store nDta to the new node nNum
    pCur->pNext = pStack;   //new node will be linked to the previous top of the stack pStack

    // returns the new node
    return pCur;
}

/*
Purpose: This function will push the next value to the top of the stack

@param pStack : LinkedStack *pStack - a pointer to the stack structure
@param nNum : int - to store the new node

Returns: void
*/
void pushLinkedStack(singlyLinkedStack *pStack, int nNum)
{
    //add a new node, then update pTop
    pStack->pTop = add_node(pStack->pTop, nNum);
}

/*
Purpose: This function pops the top element from the stack and returns the value

@param pStack : LinkedStack *pStack - a pointer to the stack structure

Returns: 0 - empty, int - value popped from the stack
*/
int popLinkedStack(singlyLinkedStack *pStack)
{
    //variable to store the popped value
    int nNum;

    //if stack is empty, return 0
    if(emptyLinkedStack(pStack)){
        return 0;
    }

    singlyStackType *pTemp = pStack->pTop;    //set *pTemp to be pTop
    nNum = pTemp->nData;                      //place the nData in nNum
    pStack->pTop = pTemp->pNext;              //pTop will be placed to the next node

    //free the removed node
    free(pTemp);

    //returns the popped value
    return nNum;
}

/*
Purpose: This function pops the top element from the stack and returns the value

@param pStack : singlyLinkedStack *pStack - a pointer to the stack structure

Returns: 0 - empty, int - value at the top of the stack
*/
int peekLinkedStack(singlyLinkedStack *pStack)
{
    if(emptyLinkedStack(pStack)){
        return 0;
    }else{
        return pStack->pTop->nData;
    }
}

/*
Purpose: This function clears all the nodes available in the stack

@param pStack : LinkedStack *pStack - a pointer to the stack structure

Returns: void
*/
void clearLinkedStack(singlyLinkedStack *pStack)
{
    //pop until all nodes are freed
    while(!emptyLinkedStack(pStack)){
        popLinkedStack(pStack);
    }
}
