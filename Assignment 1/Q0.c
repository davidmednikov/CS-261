/* CS261- Assignment 1 - Q. 0*/
/* Name: David Mednikov
 * Date: 09/25/17
 * Solution description: Print the value and address of some ints and int pointers
 */
 
#include <stdio.h>
#include <stdlib.h>

/*
fooA()
returns: void
params: int* iptr
prints the value that iptr points to, the address that iptr points to, and the address of iptr itself
*/
void fooA(int* iptr){
    printf("%d\n", *iptr); // print the value that iptr points to
     
    printf("%p\n", iptr); // print the address that iptr points to
     
    printf("%p\n", &iptr); // print the address of iptr itself
}

/*
main()
Declares an integer, prints the address of the int, passes the int to fooA, then prints the value of the int
*/
int main(){
    
    int x = 100; // initialize and declare that x = 100
    
    printf("\n%p\n", &x); // print address of int x
    
    fooA(&x); // pass address of x to fooA
    
    printf("%d\n\n", x); // print value of int x
    
    return 0; // end program
}
