/* CS261- Assignment 1 - Q.1*/
/* Name: David Mednikov
 * Date: 09/25/17
 * Solution description: Create and view a database of students.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id; // unique ID of student
	int score;
};

/*
allocate()
returns: struct student*
params: none
allocates a memory block for an array of 10 students and returns pointer to the block
*/
struct student* allocate(){
     struct student* ptr = malloc(10 * sizeof(*ptr)); // allocate memory for 10 students
     
     return ptr; // return pointer to 1st student
}

/*
allocate()
returns: none
params: struct student* students
fills the array of students with 10 generated students, each of which has a random but unique ID and a random score
*/
void generate(struct student* students)
{
    int usedIDs[10]; // keep track of used IDs so that they are unique
    
    for (int i = 0; i < 10; ++i) // initialize ints
        usedIDs[i] = 0;
    
    for (int i = 0; i < 10; ++i) // loop through array of students
    {     
         int gen = rand() % 10 + 1; // generate random number between 1 and 10
         
         while (usedIDs[gen - 1] == gen) // check to see if number already exists in usedIDs array
         {
             gen = rand() % 10 + 1; // if number already exists, generate new one until it is unique
         }
         
         usedIDs[gen - 1] = gen; // add new ID to array of used IDs
         students[i].id = gen; // pass ID to student
         students[i].score = rand() % 101; // generate random score between 0 and 100
     }     
}

/*
output()
returns: none
params: struct student* students
prints the id and score of each student in the array
*/
void output(struct student* students){
     printf("\n");
     
     for (int i = 0; i < 10; ++i) // loop through 10 students, printing out each student's id and score
         printf("%3d  %d\n", students[i].id, students[i].score);
}

/*
summary()
returns: none
params: struct student* students
prints the minimum score, maximum score, and average score of the 10 students
*/
void summary(struct student* students){
     int min, max, sum; // declare variables to keep track
     double avg;
     
     min = students[0].score; // at start, 1st student is lowest score
     max = students[0].score; // 1st student is also the highest score
     sum = students[0].score; // start running sum with 1st student
    
    for (int i = 1; i < 10; ++i) { // loop through students
             if (students[i].score < min) // if current student's score is lower than min
                 min = students[i].score; // update min to current student's score 
             
             if (students[i].score > max) // if current student's score is higher than max
                 max = students[i].score; // update max to current student's score
             
             sum += students[i].score; // add current student's score to running sum
         }
     
     avg = sum / 10.0; // divide sum by 10 to find average
     
     printf("\nMinimum score: %d\n", min); // print min
     printf("Maximum score: %d\n", max); // print max
     printf("Average score: %f\n\n", avg); // print average
}

/*
deallocate()
returns: none
params: struct student* stud
clears the memory allocated at the pointer
*/
void deallocate(struct student* stud){
     if (stud == NULL)
        printf("There is nothing to clear.\n");
     else 
        free(stud);
}

/*
main()
allocates memory for 10 students, generates the array of 10 students, prints each student's id and score, prints min, max, and avg scores of students, and clears allocated memory
*/
int main(){
    srand(time(NULL)); // seed rand to clock
    
    struct student* stud = NULL; // declare array of students
    
    stud = allocate(); // allocate memory for 10 students
    
    generate(stud); // generate 10 students, assign unique ids and random scores
    
    output(stud); // print list of 10 students with their ids and scores
        
    summary(stud); // print max, min, and avg scores of students
    
    deallocate(stud); // clear allocated memory

    return 0;
}
