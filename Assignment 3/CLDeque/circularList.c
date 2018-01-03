/*********************************************************************
** Program Filename: Assignment 3 - circularList.c
** Author: David Mednikov
** Date: 10/15/17
** Description: Implement a circular doubly linked list and its functions
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	list->sentinel = malloc(sizeof(struct Link)); // allocate memory for sentinel
	list->sentinel->next = list->sentinel; // point sentinel to itself
	list->sentinel->prev = list->sentinel; // point sentinel to itself
	list->size = 0; // set size to 0
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link* newLink = malloc(sizeof(struct Link)); // allocate memory for new link
	newLink->value = value; // set value of link
	newLink->next = NULL; // initialize pointers to NULL
	newLink->prev = NULL;
	return newLink; // return address to link
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != NULL); // list is not null
	
	struct Link* newLink = createLink(value); // create new link
	struct Link* oldLink = link->next; // keep track of old link for reassigning pointers
	
	/* update pointers so that link is inserted after the user-provided link but before old link */
	link->next = newLink; 
	newLink->next = oldLink;
	oldLink->prev = newLink;
	newLink->prev = link;	
	
	list->size++; // increment size by 1
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert(list!= NULL); // list is not null
	assert(list->size > 0); // links to remove
	
	struct Link* previous = link->prev; // link to left of link being removed
	struct Link* nextLink = link->next; // link to right of link being removed
	
	/* connect two links above to each other */
	previous->next = nextLink;
	nextLink->prev = previous;
	
	/* removed link's pointers to NULL */
	link->next = NULL;
	link->prev = NULL;
	
	free(link); // deallocate memory for link
	
	list->size--; // decrement size by 1
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	while(!circularListIsEmpty(list)) // while list is not empty
		circularListRemoveFront(list); // remove and deallocate front element
	
	/* set sentinel pointers to NULL and deallocate sentinel */
	list->sentinel->next = NULL;
	list->sentinel->prev = NULL;
	free(list->sentinel);
	
	free(list); // deallocate list pointer
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	addLinkAfter(list,list->sentinel,value); // add after sentinel
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	addLinkAfter(list,list->sentinel->prev,value); // add after last element
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	assert(list != NULL); // list is not null
	assert(list->size > 0); // list has elements
	
	return list->sentinel->next->value; // return value of front element
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert(list != NULL); // list is not null
	assert(list->size > 0); // list has elements
	
	return list->sentinel->prev->value; // return value of back element
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	removeLink(list,list->sentinel->next); // remove front element
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	removeLink(list,list->sentinel->prev); // remove back element
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	assert(list != NULL); // list is not null
	
	if (list->size == 0) // return 1 if list is empty
		return 1;
	
	return 0; // list is not empty
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	assert(list != NULL); // list is not empty
	assert(list->size > 0); // list has elements
	
	struct Link* currentLink = list->sentinel->next; // iterator
	
	printf("\n"); // blank like
	
	while (currentLink != list->sentinel) // iterate through loop
	{
		printf("%g\n",currentLink->value); // print current value
		currentLink = currentLink->next; // move to next link
	}
	
	printf("\n"); // blank line
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	int swaps; // number of swaps
	int copyFromFront; // number copied from front half
	int copyFromBack; // number copied from back half
	
	assert(list != NULL); // list is not empty
	assert(list->size > 0); // list has elements
	
	swaps = list->size / 2; // calcultae number of swaps and drop remainder
	
	/* iterators to move through list */
	struct Link* frontIterator = list->sentinel->next;
	struct Link* backIterator = list->sentinel->prev;
	
	for (int i = 1; i <= swaps; i++) // perform number of swaps
	{
		copyFromFront = frontIterator->value; // front int to temp variable
		copyFromBack = backIterator->value; // back int to temp variable
		
		frontIterator->value = copyFromBack; // copy back int to front
		backIterator->value = copyFromFront; // copy front int to back
		
		/* move iterators toward middle of list */
		frontIterator = frontIterator->next; 
		backIterator = backIterator->prev;
	}
}
