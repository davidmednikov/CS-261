/*********************************************************************
** Program Filename: Assignment 4 - toDoList.c
** Author: David Mednikov
** Date: 11/12/17
** Description: Implement a to do list using a heap
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TYPE createTask (int priority, char *desc) 
{
	TYPE newTask;
	newTask.priority = priority;
	strcpy(newTask.description, desc);
	return newTask;
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the 
			task priority, followed by a tab character (\t), and 
			the task description.
			
			The tasks are not necessarily stored in the file in 
			priority order. 
	
*/
void saveList(DynArr *heap, FILE *filePtr)
{
  	int tasks = heap->size; // number of tasks to copy
	int i; // iterator variable
	
	for (i = 0; i < tasks; i++) // loop through heap
	{
		TYPE task = getDynArr(heap, i); // get task at index
		int priority = task.priority; // store priority in int
		char* description = task.description; // store description as string
		fprintf(filePtr, "%-4d%s\r\n", priority, description); // pring the priority and description to the file and match the input format
	}
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file				
*/
void loadList(DynArr *heap, FILE *filePtr)
{	
	int currentChar = getc(filePtr); // start with 1st character
	
	while(currentChar != -1 && currentChar != 4) // not end of message
	{
		while (currentChar != 10) // while not a newline
		{
			/* This function will read the priority and save it to an int, then skip the whitespace, then read the description and save it to a string. Repeats for each line */
			
			/* Get Priority Int */
			
			char *priority = malloc(sizeof(char) * 4); // allocate char array string for 3 digits
			for (int i = 0; i < 4; i++) // initialize char array
				priority[i] = 0; // set each char to NULL
			
			int digit = 0; // iterator
			int priorityVal; // int to hold priority
						
			while(currentChar != 9 && currentChar != 32) // while not spaces or tabs
			{
				priority[digit] = currentChar; // copy char to char array
				digit++; // increment iterator
				currentChar = getc(filePtr); // get next char from file
			}
			
			char *ptr;
			priorityVal = strtol(priority, &ptr, 10); // convert char array to int
			
			free(priority); // clear allocated memory for digit string
						
			/* Get Description */
			
			// space or tab, skip these characters
			while(currentChar == 9 || currentChar == 32)
				currentChar = getc(filePtr); // move to next character
			
			char *desc = malloc(sizeof(char) * 129); // allocate memory for 128 character description
			for (int i = 0; i < 129; i++) // set each char to NULL
				desc[i] = 0;
			
			int index = 0; // iterator
									
			while(currentChar != 13 && currentChar != 10) // while not new line or carriage return
			{
				desc[index] = currentChar; // copy char to string
				currentChar = getc(filePtr); // move to next char
				index++; // increment iterator
			}
			
			TYPE newTask = createTask(priorityVal, desc); // create task from priority int and description string
			addHeap(heap, newTask); // add new task to heap
						
			currentChar = getc(filePtr); // move to end of row
			
			free(desc); // free allocated memory for string
		}
		
		currentChar = getc(filePtr); // move to next line
	}
}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
  	int size = heap->size; // get size
	int i; // iterator
	
	DynArr copy; // create array struct for copying
	copyDynArr(heap, &copy); // copy array to new array
	
	sortHeap(&copy); // sort the copied array
	
	for (i = size - 1; i >= 0; i--) // loop through sorted array
	{
		TYPE task = getDynArr(&copy, i); // get task at current index
		printf("\n%-3d: %s\n", task.priority, task.description); // save task to file
	}
	
	printf("\n");
	
	freeDynArr(&copy); // free copied array from memory
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
	ret: 	-1 if priority of left < priority of right
			1 if priority of left > priority of right
			0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right)
{
	if (left.priority < right.priority)
		return -1;
	else if (left.priority > right.priority)
		return 1;
	else
		return 0;
}
