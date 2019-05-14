/* CS261- Assignment 1 - Q.2*/
/* Name: Brittany Dunn
 * Date: July 10, 2018
 * Solution description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
     int* temp;
     temp = a; 
     a = b;
     b = temp;
    /*Decrement the value of integer variable c*/
     c--;
    /*Return c*/
     return c;
}

int main(){
     srand(time(0));
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x = rand() % 10;
    int y = rand() % 10;
    int z = rand() % 10;
    /*Print the values of x, y and z*/
    printf("x = %i\n", x);
    printf("y = %i\n", y);
    printf("z = %i\n", z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int returnVal = foo(&x,&y,z);
    /*Print the values of x, y and z*/
    printf("x = %i\n", x);
    printf("y = %i\n", y);
    printf("z = %i\n", z);
    /*Print the value returned by foo*/
    printf("returned value = %i\n", returnVal);
/* a) The return value is different from the value of z. Z was passed by
   value so a copy of z was changed in the function not z.
   b) X and Y are not different because the addresses swaped in the function
   are done so at the local scope of the function and do not effect the 
   addresses in the main function of  x and y. */    
    return 0;
}
    
    


