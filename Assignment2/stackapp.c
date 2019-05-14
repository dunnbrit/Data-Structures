/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


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
	post:	
*/
int isBalanced(char* s)
{
    //Create stack
    DynArr * myStack = newDynArr(50);
    
    //Get first char
    char currentChar = nextChar(s);
    
    //While char is not end of string
    while (currentChar != '\0'){
	
	if(currentChar == '('){
	    //Add closing parentheses to stack
	    pushDynArr(myStack, ')');
	}
	
	else if(currentChar == '{'){
	    //Add closing brace to stack
	    pushDynArr(myStack, '}');
	}
	
	else if(currentChar == '['){
	    //Add closing bracket to stack
	    pushDynArr(myStack, ']');
	}
	
	else if(currentChar == ')'){
	    //Check if stack is empty
	    if(isEmptyDynArr(myStack) == 1){
		//If empty then return false
		return 0;
	    }
	    //Check top of stack matches current char
	    else if(topDynArr(myStack) == ')'){
		//If it does pop the top of stack
		popDynArr(myStack);
	    }
	    else{
		//If it doesn't then return false
		return 0;
	    }
	}
	
	else if(currentChar == '}'){
	    //Check if stack is empty
	    if(isEmptyDynArr(myStack) == 1){
		//If empty then return false
		return 0;
	    }
	    //Check top of stack matches current char
	    else if(topDynArr(myStack) == '}'){
		//If it does pop the top of stack
		popDynArr(myStack);
	    }
	    else{
		//If it doesn't then return false
		return 0;
	    }    
	}
	else if(currentChar == ']'){
	    //Check if stack is empty
	    if(isEmptyDynArr(myStack) == 1){
		//If empty then return false
		return 0;
	    }
	    //Check top of stack matches current char
	    else if(topDynArr(myStack) == ']'){
		//If it does pop the top of stack
		popDynArr(myStack);
	    }
	    else{
		//If it doesn't then return false
		return 0;
	    }    
	}
	
	//Check next char
	currentChar = nextChar(s);
    };
    
    //Check that when the end of string was reached the stack was empty
    if(isEmptyDynArr(myStack) == 1){
	//If stack empty then return true
	return 1;
    }
    else{
	//If stack was not empty return false
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

