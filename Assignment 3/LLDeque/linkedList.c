/*********************************************************************
** Program Filename: Assignment 3 - linkedList.c
** Author: David Mednikov
** Date: 10/15/17
** Description: Implement a doubly linked list and its functions
*********************************************************************/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	
	/* allocate memory for front and back sentinels */
	list->frontSentinel = malloc(sizeof(struct Link));
	list->backSentinel = malloc(sizeof(struct Link));
	
	/* initialize sentinel pointers */
	list->frontSentinel->next = list->backSentinel;
	list->frontSentinel->prev = NULL;
	list->backSentinel->next = NULL;
	list->backSentinel->prev = list->frontSentinel;
	
	list->size = 0; // set size to 0
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	assert(list != NULL); // list is not empty
	
	struct Link* previous = link->prev; // keep track of previous link
	struct Link* newLink = malloc (sizeof(struct Link)); // allocate memory for new link
	newLink->value = value; // set value of new link
	
	/* update pointers to/from new link */
	previous->next = newLink;
	newLink->next = link;
	newLink->prev = previous;
	link->prev = newLink;
	
	list->size++; // increment size by 1
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list != NULL); // list is not empty
	assert(list->size > 0); // elements to be removed
	
	struct Link* previous = link->prev; // keep track of link before removed link
	
	/* update pointers to remove link */
	previous->next = link->next;
	link->next->prev = previous;
	
	free(link); // deallocate memory
	list->size--; // decrement size by 1
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list,list->frontSentinel->next,value); // add link before first element
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list,list->backSentinel,value); // add link before back sentinel
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list != NULL); // list is not null
	assert(list->size > 0); // list is not empty
	return list->frontSentinel->next->value; // return value of first element
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	assert(list != NULL); // list is not null
	assert(list->size > 0); // list is not empty
	return list->backSentinel->prev->value; // return value of back element
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	removeLink(list,list->frontSentinel->next); // remove front element
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	removeLink(list,list->backSentinel->prev); // remove back element
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	assert(list != NULL); // list is not empty
	
	if (list->size == 0) // // return 1 if size is 0
		return 1;
		
	return 0; // list has elements
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	assert(list != NULL); // list is not null
	assert(list->size > 0); // elements to be printed
	
	struct Link* currentLink = list->frontSentinel->next; // iterator
	
	while(currentLink != list->backSentinel) // iterate through list
	{
		if (currentLink->next == list->backSentinel) // if last element, print an extra line
			printf("%d\n\n", currentLink->value); // print last value
		else
			printf("%d\n", currentLink->value); // print non-last values
		
		currentLink = currentLink->next; // iterate to next element
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list,list->backSentinel,value); // add link to back of list
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list != NULL); // list is not null

	if (list->size == 0) // if list is empty, it does not contain the value
		return 0; // return 0
	
	struct Link* currentLink = list->frontSentinel->next; // iterator
	
	while(currentLink != list->backSentinel) // iterate through list
	{
		if (currentLink->value == value) // current link contains value
			return 1; // value found, return 1
		currentLink = currentLink->next; // step to next link
	}
	
	return 0; // not found, return 0
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	int keepLooking = 1; // boolean to keep looking
	
	assert(list != NULL); // list is not empty
	assert(list->size > 0); // contains elements to be removed
	
	struct Link* currentLink = list->frontSentinel->next; // iterator
	
	while(keepLooking == 1) // while looking for value
	{
		if (currentLink->value == value) // value found
		{
			removeLink(list,currentLink); // remove link
			keepLooking = 0; // break out of loop
		}
		else //v value not found, step to next link
		{
			currentLink = currentLink->next; // step to next link
			
			if (currentLink == list->backSentinel) // current link is back sentinel
				keepLooking = 0; // break out of the loop
		}
	}
}
