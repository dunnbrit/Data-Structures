/* CS261- Assignment 1 - Q. 0*/
/* Name: Brittany Dunn
 * Date: July 10 2018
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void fooA(int* iptr){
  
     /*Print the value and address of the integer pointed to by iptr*/
     printf("The value iptr points to is %i\n", *iptr);
     printf("The address iptr points to is %p\n", iptr);
     /*Increment the value of the integer pointed to by iptr by 5*/
     *iptr += 5;      
     /*Print the address of iptr itself*/
    printf("The address of iptr itself is %p\n\n", &iptr);
}

void fooB(int* jptr){
  
     /*Print the value and address of the integer pointed to by jptr*/
     printf("The value jptr points to is %i\n", *jptr);
     printf("The address jptr points to is %p\n", jptr);          
     /*Decrement jptr by 1*/
      jptr--;
      printf("The address jptr points to now is %p\n", jptr);
     /*Print the address of jptr itself*/
     printf("The address of jptr itself is %p\n\n", &jptr);
}


int main(){
    srand(time(NULL));
    /*Declare an integer x and initialize it randomly to a value in [0,10] */
     int x = rand() % 10;
    /*Print the value and address of x*/
     printf("The value of x is %i\n", x); 
     printf("The address of x is %p\n\n", &x);
    /*Call fooA() with the address of x*/
     fooA(&x);
    /*Print the value of x*/
     printf("The value of x is now %i\n\n", x);
     //The value of x is different because when the function was called the
     //address of x was passed, so it was passed by reference. This means the
     //function received x instead of a copy of x.
    /*Call fooB() with the address of x*/
     fooB(&x);
    /*Print the value and address of x*/
     printf("The value of x is now %i\n", x);
     printf("The address of x is now %p\n\n", &x);
     //The value and address of x are not changed because the function fooB
     //changes the address pointed to by the local variable jptr and it does
     //not change what was originally at the address pointed to by jptr
    
    return 0;
}


