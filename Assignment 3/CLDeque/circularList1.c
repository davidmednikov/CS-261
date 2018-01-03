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
	list->sentinel = malloc(sizeof(struct Link));
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link* newLink = malloc(sizeof(struct Link));
	newLink->value = value;
	newLink->next = NULL;
	newLink->prev = NULL;
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != NULL);
	struct Link* newLink = createLink(value);
	
	struct Link* oldLink = link->next;
	link->next = newLink;
	newLink->next = oldLink;
	oldLink->prev = newLink;
	newLink->prev = link;	
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert(list!= NULL);
	assert(list->size > 0);
	
	struct Link* previous = link->prev;
	struct Link* nextLink = link->next;
	
	previous->next = nextLink;
	nextLink->prev = previous;
	
	link->next = NULL;
	link->prev = NULL;
	free(link);
	
	list->size--;
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
	assert(list != NULL);
	
	struct Link* currentLink = list->sentinel->next;
	
	if (list->size == 0)
	{
		free(currentLink);
	}
	else
	{
		while(currentLink != list->sentinel)
		{
			currentLink = currentLink->next;
			free(currentLink->prev);
		}
		
		free(currentLink);
	}
	
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	assert(list != NULL);
	
	struct Link* newLink = malloc(sizeof(struct Link));
	newLink->value = value;
	
	struct Link* front = list->sentinel->next;
	
	newLink->next = front;
	front->prev = newLink;
	list->sentinel->next = newLink;
	newLink->prev = list->sentinel;
	
	list->size++;
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	assert(list != NULL);
	
	struct Link* newLink = malloc(sizeof(struct Link));
	newLink->value = value;
	
	struct Link* back = list->sentinel->prev;
	
	back->next = newLink;
	newLink->prev = back;
	newLink->next = list->sentinel;
	list->sentinel->prev = newLink;
	
	list->size++;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	assert(list != NULL);
	assert(list->size > 0);
	
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert(list != NULL);
	assert(list->size > 0);
	
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(list != NULL);
	assert(list->size > 0);
	
	struct Link* toRemove = list->sentinel->next;
	struct Link* newFront = toRemove->next;
	
	list->sentinel->next = newFront;
	newFront->prev = list->sentinel;
	
	toRemove->next = NULL;
	toRemove->prev = NULL;
	
	free(toRemove);
	
	list->size--;
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	assert(list != NULL);
	assert(list->size > 0);
	
	struct Link* toRemove = list->sentinel->prev;
	struct Link* newBack = toRemove->prev;
	
	list->sentinel->prev = newBack;
	newBack->next = list->sentinel;
	
	toRemove->next = NULL;
	toRemove->prev = NULL;
	
	free(toRemove);
	
	list->size--;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	assert(list != NULL);
	
	if (list->size == 0)
		return 1;
	
	return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	assert(list != NULL);
	assert(list->size > 0);
	
	struct Link* currentLink = list->sentinel->next;
	
	printf("\n");
	
	while (currentLink != list->sentinel)
	{
		printf("%f\n",currentLink->value);
		currentLink = currentLink->next;
	}
	
	printf("\n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	int swaps;
	int copyFromFront;
	int copyFromBack;
	
	assert(list != NULL);
	assert(list->size > 0);
	
	swaps = list->size / 2;
	
	struct Link* frontIterator = list->sentinel->next;
	struct Link* backIterator = list->sentinel->prev;
	
	for (int i = 1; i <= swaps; i++)
	{
		copyFromFront = frontIterator->value;
		copyFromBack = backIterator->value;
		
		frontIterator->value = copyFromBack;
		backIterator->value = copyFromFront;
		
		frontIterator = frontIterator->next;
		backIterator = backIterator->prev;
	}
}
