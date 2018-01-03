/* CS261- Assignment 1 - Q.4*/
/* Name: David Mednikov
 * Date: 09/27/17
 * Solution description: create an array of n students, generate a random ID and score for each student, print the array of students, sort the array, then print again
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

struct student{
	int id; // unique ID
	int score; // score
};

/*
sort()
returns: none
params: struct student* students, int n
sorts array of students using bubble sort
*/
void sort(struct student* students, int n){
     
    int iterationsLeft = n; // keep track of number of iterations left
    
    while (iterationsLeft > 0) // while still unsorted
    {
        for (int i = 0; i < iterationsLeft - 1; ++i)// loop through all students in array
        {
            if (students[i].score > students[i+1].score) // if score of current student is greater than score of next student
            {
                struct student temp = students[i]; // hold current student in temp student
                students[i] = students[i+1]; // copy next student to current element
                students[i+1] = temp; // copy temp student to next eleemnt
            }
        }
        
        --iterationsLeft; // decrement iterations left by 1
    }
    
}

/*
main()
allocates memory for an array of 25 studemts, randomly generates an ID and score for each student in the array, prints the array, then sorts and prints the array again
*/
int main(){
    int n = 25;
    srand(time(NULL)); // seed rand to clock
    
    struct student* students = malloc(n * sizeof(students)); /*Allocate memory for n students using malloc.*/
    
    int usedIDs[n];  // keep track of used IDs so that they are unique
    
    for (int i = 0; i < n; ++i) // loop through array of students
        usedIDs[i] = 0; // initialize ints
    
    for (int i = 0; i < n; ++i) // loop through array of students
    { 
         int gen = rand() % n + 1; // generate random number between 1 and n
         while (usedIDs[gen - 1] == gen) // check to see if ID already exists in usedIDs array
         {
             gen = rand() % n + 1; // if ID already exists, generate new one until it is unique
         }
         usedIDs[gen - 1] = gen; // add new ID to array of used IDs
         students[i].id = gen; // pass ID to student
         students[i].score = rand() % 101; // generate random score between 0 and 100
     }     
    
    printf("\n ID | Score\n ‾‾‾|‾‾‾‾‾\n"); // table header
    
    for (int i = 0; i < n; ++i) // loop through array of students
        printf("%3d | %d\n", students[i].id, students[i].score); // print each student ID and score
     
    sort(students, n); // sort students by score
     
    printf("\n\n ID | Score\n ‾‾‾|‾‾‾‾‾\n"); // table header
    
    for (int i = 0; i < n; ++i) // loop through array of students
        printf("%3d | %d\n", students[i].id, students[i].score); // print each student id and score, should now be sorted
    
    printf("\n");
    
    free(students);
    
    return 0;
}
