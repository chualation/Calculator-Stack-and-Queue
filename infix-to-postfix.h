#ifndef INFIX_TO_POSTFIX_H
#define INFIX_TO_POSTFIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h" // stack header file
#include "queue.h" // queue header file

//Arithmetic Operators
#define ADDITION -1                 // +
#define SUBTRACTION -2              // -
#define MULTIPLICATION -3           // *
#define MODULO -4                   // %
#define EXPONENTIAL -5              // ^
#define DIVISION -6                 // /

//Relational Operators
#define GREATER -7                  // >
#define LESS -8                     // <
#define GREATER_EQUAL -9            // >=
#define LESS_EQUAL -10              // <=
#define NOT_EQUAL -11               // !=
#define EQUAL -12                   // ==

//Logical Operators
#define NOT -13                     // !
#define AND -14                     // &&
#define OR -15                      // ||

//Parentheses Symbols
#define OPEN -16                    // (
#define CLOSE -17                   // )

/*
Purpose: A struct to represent 2 character operators

@ pSymbol : a pointer to the operator string
@ nOP : corresponds to the value defined by the constants (#define)
*/
typedef struct{
    const char *pSymbol;
    int nOP;
}twoCharOP;

/*
Purpose: A struct to represent 1 character operators

@ nSymbol : a single character symbol
@ nOP : corresponds to the value defined by the constants (#define)
*/
typedef struct{
    char nSymbol;
    int nOP;
}oneCharOP;
 
int operatorPrecedence(int nOP);
int isRightAssociative(int nOP);
int isOperatorValid(const char nArr[], int i, int *nLength, int *nVal);
void handleClosingParenthesis(singlyLinkedStack *pStack, singlyLinkedQueue *pQueue);
void processOperators(int nVal, singlyLinkedStack *pStack, singlyLinkedQueue *pQueue);
void convertToPostfix(const char *pInfix, singlyLinkedQueue *pQueue);

#endif
