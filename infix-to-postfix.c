#include "infix-to-postfix.h" // header file 

/*
Purpose: This function will return the precedence level of the operator 

@param  nOP : the value of the operator to be checked

Returns: precedence level (6 - highest, 0 - lowest, -1 - invalid)
*/
int operatorPrecedence(int nOP)
{
    if(nOP == NOT){
        return 6; //highest precedence for operators
    }else if(nOP == EXPONENTIAL){
        return 5;
    }else if(nOP == MULTIPLICATION || nOP == DIVISION || nOP == MODULO){
        return 4;
    }else if(nOP == ADDITION || nOP == SUBTRACTION){
        return 3;
    }else if(nOP == GREATER || nOP == LESS || nOP == GREATER_EQUAL || nOP == LESS_EQUAL || nOP == EQUAL || nOP == NOT_EQUAL){
        return 2;
    }else if(nOP == AND){
        return 1;
    }else if(nOP == OR){
        return 0; //lowest precedence for operators
    }else{
        return -1; //invalid operator
    }
}

/*
Purpose: This function checks if the operator is right-associative

@param nOP : the value of the operator to be checked

Returns: 1 - right associative, 0 - not right associative
*/
int isRightAssociative(int nOP)
{
    //only EXPONENTIAL and NOT are right-associative operators
    if(nOP == EXPONENTIAL){
        return 1;
    }else if(nOP == NOT){
        return 1;
    }else{
        return 0;
    }
}

/*
Purpose: This function will determine whether the current characters form a valid operator

@param nArr : contains the infix expression as an array
@param i : current index to be checked by the function
@param nLength : a pointer to store the length  of the operator
@param nVal : a pointer to store the value of the operator

Returns: 1 - valid, 0 - not valid
*/
int isOperatorValid(const char nArr[], int i, int *nLength, int *nVal)
{
    //initialize the tables for 1 and 2 character operators
    twoCharOP nTwoCharArr[] = {{">=", GREATER_EQUAL}, {"<=", LESS_EQUAL}, {"!=", NOT_EQUAL}, {"==", EQUAL}, {"&&", AND}, {"||", OR}};
    oneCharOP nOneCharArr[] = {{'+', ADDITION}, {'-', SUBTRACTION}, {'*', MULTIPLICATION}, {'%', MODULO}, {'^', EXPONENTIAL}, {'/', DIVISION},
                               {'>', GREATER}, {'<', LESS}, {'!', NOT}, {'(', OPEN}, {')', CLOSE}};

    // Check if the operator has 2 characters 
    for(int j = 0; j < sizeof(nTwoCharArr)/sizeof(nTwoCharArr[0]); j++){
        if(nArr[i] == nTwoCharArr[j].pSymbol[0] && nArr[i+1] == nTwoCharArr[j].pSymbol[1]){
            *nLength = 2;                   //store the length of the operator
            *nVal = nTwoCharArr[j].nOP;     //store the corresponding value
            return 1; 
        }
    }

    *nLength = 1;

    // Check if the operator has 1 character
    for(int j = 0; j < sizeof(nOneCharArr)/sizeof(nOneCharArr[0]); j++){
        if(nArr[i] == nOneCharArr[j].nSymbol){
            *nVal = nOneCharArr[j].nOP;     //store the corresponding value
            return 1;
        }
    }

    return 0;
}

/*
Purpose: This function will handle the closing parenthesis by popping and enqueuing the operators

@param pStack : singlyLinkedStack *pStack - a pointer to the stack structure
@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue

Returns: void
*/
void handleClosingParenthesis(singlyLinkedStack *pStack, singlyLinkedQueue *pQueue)
{
    //pop the operator until an open parenthesis (OPEN) is found in the expression
    while(!emptyLinkedStack(pStack) && peekLinkedStack(pStack) != OPEN){
        enqueueLinkedQueue(pQueue, popLinkedStack(pStack));
    }

    //remove the open parenthesis (OPEN)
    if(!emptyLinkedStack(pStack) && peekLinkedStack(pStack) == OPEN){
        popLinkedStack(pStack);
    }
}

/*
Purpose: This function will process an operator by popping high/equal precedence operators and enqueue them into the postfix queue

@param nVal : the operator to be processed by the function 
@param pStack : singlyLinkedStack *pStack - a pointer to the stack structure
@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue

Returns: void
*/
void processOperators(int nVal, singlyLinkedStack *pStack, singlyLinkedQueue *pQueue)
{
    int nTop;               //handles the operator at the top of the stack
    int nTopPrecedence;     //precedence of nTop operator
    int nCurrentPrecedence; //precedence of the current operator that is being evaluated

    //while the precedence rules are valid, pop the operators from the stack
    while(!emptyLinkedStack(pStack)){
        nTop = peekLinkedStack(pStack);                 //initialize to look at the top operator present in the stack
        nTopPrecedence = operatorPrecedence(nTop);      //initialize to get the precedence of the top operator 
        nCurrentPrecedence = operatorPrecedence(nVal);  //initialize to get the precedence of the current operator being evaluated

        //based on the precedence and associativity of the operator, pop the stack
        if((isRightAssociative(nVal) && nCurrentPrecedence < nTopPrecedence) || (!isRightAssociative(nVal) && nCurrentPrecedence <= nTopPrecedence )){
            if(nTop == OPEN){ //stop aat the opening parenthesis (OPEN)
                break;
            }else{
                enqueueLinkedQueue(pQueue, popLinkedStack(pStack)); //move to the next
            }
        }else{
            break; //stop popping if there are no more precedence issues found
        }
    }
    pushLinkedStack(pStack, nVal); //push the current opertor to the stack
}

/*
Purpose: This function will convert the infix expression to a postfix expression

@param pInfix : infix expression
@param pQueue : singlyLinkedQueue *pQueue - a pointer to the queue

Returns: void
*/
void convertToPostfix(const char *pInfix, singlyLinkedQueue *pQueue)
{
    int i = 0;                  //index for traversing in the infix expression
    int nNum, nLength, nVal;    //nNum - to store the value read from the expression
                                //nLength - to store the length of the operator (1 or 2 characters)
                                //nVal - to store the numeric value of the operator

    singlyLinkedStack nStack;           //initialize the stack for operators
    initializeLinkedStack(&nStack);     //initialize the stack to be empty before called

    //while the character is not the end of the string, evaluate the expression
    while(pInfix[i] != '\0'){
        //read the number if the current character is a digit
        if(pInfix[i] >= '0' && pInfix[i] <= '9'){
            nNum = 0;
            //convert the characters into integer value
            while(pInfix[i] >= '0' && pInfix[i] <= '9'){
                nNum = nNum * 10 + (pInfix[i] - '0');
                i++;
            }
            enqueueLinkedQueue(pQueue, nNum); //add the number to the postfix queue
        }else{
            //checks if the current character forms a  valid operator
            if(isOperatorValid(pInfix, i, &nLength, &nVal)){
                if (nVal == OPEN){
                    pushLinkedStack(&nStack, nVal); //push the open parenthesis (OPEN) onto the stack
                }else if(nVal == CLOSE){
                    handleClosingParenthesis(&nStack, pQueue); //processes the close parenthesis (CLOSE)
                }else{
                    processOperators(nVal, &nStack, pQueue); //processes the other operators
                }
                i += nLength; //move the index by the length of the operator
            }else{
                i++; //skip invalid characters
            }
        }
    }

    //while the stack is not empty, pop all remaining operators and add them to the postfix queue
    while(!emptyLinkedStack(&nStack)){
        enqueueLinkedQueue(pQueue, popLinkedStack(&nStack));
    }

    //clear the stack
    clearLinkedStack(&nStack);
}
