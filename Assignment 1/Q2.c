/* CS261- Assignment 1 - Q.2*/
/* Name: David Mednikov
 * Date: 09/25/17
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

/*
foo()
returns: int
params: int* a, int* b, int c
doubles the value pointed to by a, halves the value pointed to by b, and returns the sum of the updated values of a and b
*/
int foo(int* a, int* b, int c){
    *a *= 2; // double value pointed to by a
    
    *b /= 2; // half value pointed to by b
    
    c = *a + *b; // sum of values pointed to by a and b
    
    return c; // return sum
}


/*
main()
prints three integers, passes two by reference and one by value to foo(), and prints the three integers again
*/
int main(){
    int x = 5; // declare variables
    int y = 6;
    int z = 7;
    int fooResult;
    
    printf("\nx = %d", x); // print variables
    printf("\ny = %d", y);
    printf("\nz = %d", z);
    
    fooResult = foo(&x, &y, z); // pass pointers to x and y and value of z to foo, return to fooResult
    
    printf("\n\nfoo returns %d\n\n", fooResult); // print the return of foo
    
    printf("x = %d", x); // print updated variables
    printf("\ny = %d", y);
    printf("\nz = %d\n\n", z);
 
    /*Is the return value different than the value of z?  Why?*/
    
    // Yes, because foo takes int z by value as opposed to by reference. Therefore the value of z is never actually changed. When foo returns c to main, it is returning a local copy of c, and not actually overwriting global int z.
    
    return 0;
}
    
    
