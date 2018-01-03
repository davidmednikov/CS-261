/***********************************************************************************
** Program Filename: Assignment 2 - stackapp.c
** Author: David Mednikov
** Date: 10/4/17
** Description: Using a stack, check if an inputted string is balanced - i.e., for
** every opening parentheses, square bracket, or curly bracket, there must be a closing 
** bracket of the same type before any other bracket is encountered. All parentheses
** and brackets must be closed for the string to be balanced.
***********************************************************************************/


/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"

struct DynArr // dynamic array sruct definition
{
	TYPE *data;		/* pointer to the data array */
};

/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	returns 1 if balanced, 0 if not.
*/
int isBalanced(char* s)
{
	if (s == NULL) // if there is no string, it is balanced
		return 1;
	
	DynArr *stack; // define stack
	stack = newDynArr(10); // initialize array and allocate memory for 100 stack variables
	
	char next = nextChar(s); // get next character

	while (next != '\0') // while next character is not end of string
	{
		if (next == '{' || next == '[' || next == '(') // opening bracket/parantheses (b/p), add to stack
			pushDynArr(stack, next);
		
		else if (next == '}' || next == ']' || next == ')') // closing b/p
		{
			if (isEmptyDynArr(stack)) // no opening b/p on stack, not balanced
			{
				deleteDynArr(stack);
				return 0;
			}
			
			if (next == '}' && topDynArr(stack) != '{') // opening b/p not of same type, not balanced
			{	
				deleteDynArr(stack);
				return 0;
			}
			else if (next == '}' && topDynArr(stack) == '{') //  matching opening b/p, pop top from stack
				popDynArr(stack);
			
			if (next == ']' && topDynArr(stack) != '[') // not of same type, not balanced
			{
				deleteDynArr(stack);
				return 0;
			}
			else if (next == ']' && topDynArr(stack) == '[') // same type, pop
				popDynArr(stack);
			
			if (next == ')' && topDynArr(stack) != '(') // not of same type, not balanced
			{
				deleteDynArr(stack);
				return 0;
			}
			else if (next == ')' && topDynArr(stack) == '(') // same type, pop
				popDynArr(stack);
		}

		next = nextChar(s); // go to next character
	}
	
	if (isEmptyDynArr(stack)) // all opening b/p's have been closed
	{
		deleteDynArr(stack);
		return 1;
	}
	else // unclosed b/p, not balanced
	{
		deleteDynArr(stack);
		return 0;
	}
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

