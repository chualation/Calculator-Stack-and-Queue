#include <stdio.h>
#include <string.h>
#include "stack.C"              //stck source file
#include "queue.c"              //queue source file
#include "infix-to-postfix.c"   //infix-to-postfix source file
#include "evaluation.c"         //evaluation source file


/*
Purpose: This is the main function of the program

@param  

Returns: 0
*/
int main()
{
    char nInfix[257];                   //stores the infix expression input of the user
    int nCount;                         //stores the number of nodes in the queue
    int nError, nResult;                //nError - flg for division/modulo by zero error
                                        //nResult - final result
    singlyLinkedQueue nPostfix;         //initialize to store the postfix expression
    initializeLinkedQueue(&nPostfix);   //initiliaze the queue to be empty

    //read the input infix expression
    while(fgets(nInfix, sizeof(nInfix), stdin)){
        //remove any newline characters from the input
        for(int i = 0; nInfix[i] != '\0'; i++){
            if (nInfix[i] == '\n'){
                nInfix[i] = '\0';
                break;
            }
        }

        //Stop the program once "QUIT" is inputed into the program
        if(strcmp(nInfix, "QUIT") == 0){
            break;
        }

        //Skip empty lines
        if(strlen(nInfix) == 0){
            continue;
        }

        convertToPostfix(nInfix, &nPostfix);    //convert the infix expression to postfix expression

        nCount = countNodes(&nPostfix);         //initiliaze nCount to the number of nodes in the queue

        //evaluate only if the expression has valid inputs
        if(nCount >= 3){
            printQueue(&nPostfix);                          //print the postfix expression

            nError = 0;                                     //initialize the flag to 0
            nResult = evaluatePostfix(&nPostfix, &nError);  //innitialize nResult to evaluate the postfix expression

            //check if division/modulo by zero occurs
            if(nError){
                printf("Division by zero error!\n");
            }else{
                printf("%d\n", nResult);
            }
        }
        clearLinkedQueue(&nPostfix);    //clear the queue
        printf("\n");
    }
    return 0;
}
