/* CS261- Assignment 1 - Q.3*/
/* Name: David Mednikov
 * Date: 09/25/17
 * Solution description: create and sort an array of 20 integers
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
sort()
returns: none
params: int* number, int n
sorts array of integers using bubble sort
*/
void sort(int* number, int n){
     
    int iterationsLeft = n; // keep track of number of iterations left
    
    while (iterationsLeft > 0) // while still unsorted
    {
        for (int i = 0; i < iterationsLeft - 1; ++i) // loop through all numbers in array
        {
            if (number[i] > number[i+1]) // if number at current element is greater than number at next element
            {
                int temp = number[i]; // hold current value in temp variable
                number[i] = number[i+1]; // copy value from next element to current element
                number[i+1] = temp; // copy temp int to next eleemnt
            }         
        }
        
        --iterationsLeft; // decrement iterations left by 1
    }

}

/*
main()
allocates memory for an array of 20 integers, randomly generates a number for each element of the array, prints the array, then sorts and prints the array again
*/
int main(){
    int n = 20; // declare number of integers
    srand(time(NULL)); // seed rand to clock
    
    int* ptr = malloc(n * sizeof(n)); // allocate memory for n integers
    
    for (int i = 0; i < n; ++i) // loop through each element
        ptr[i] = rand(); // generate random number in each element
    
    printf("\n");
    
    for (int i = 0; i < n; ++i) // loop through each element
        printf("%d\n", ptr[i]); // print each element

    sort(ptr, n); // sort array
    
    printf("\nSorted:\n\n");
    
    for (int i = 0; i < n; ++i) // loop through each element
        printf("%d\n", ptr[i]);  // print each element, should now be sorted
        
    printf("\n");
    
    free(ptr);
    
    return 0;
}
