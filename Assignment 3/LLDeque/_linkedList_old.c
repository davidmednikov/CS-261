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
	list->frontSentinel = malloc(sizeof(struct Link));
	list->backSentinel = malloc(sizeof(struct Link));
	list->frontSentinel->next = list->backSentinel;
	list->frontSentinel->prev = NULL;
	list->backSentinel->next = NULL;
	list->backSentinel->prev = list->frontSentinel;
	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	assert(list != NULL);
	struct Link* previous = link->prev;
	struct Link* newLink = malloc (sizeof(struct Link));
	newLink->value = value;
	previous->next = newLink;
	newLink->next = link;
	newLink->prev = previous;
	link->prev = newLink;
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list != NULL);
	assert(list->size > 0);
	struct Link* previous = link->prev;
	previous->next = link->next;
	link->next->prev = previous;
	free(link);
	list->size--;
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
	assert(list != NULL);
	struct Link* first = list->frontSentinel->next;
	struct Link* newLink = malloc (sizeof(struct Link));
	list->frontSentinel->next = newLink;
	newLink->value = value;
	newLink->next = first;
	newLink->prev = list->frontSentinel;
	first->prev = newLink;
	list->size++;
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);
	struct Link* last = list->backSentinel->prev;
	struct Link* newLink = malloc (sizeof(struct Link));
	newLink->value = value;
	last->next = newLink;
	list->backSentinel->prev = newLink;
	newLink->prev = last;
	newLink->next = list->backSentinel;
	list->size++;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list != NULL);
	assert(list->size > 0);
	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	assert(list != NULL);
	assert(list->size > 0);
	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list != NULL);
	assert(list->size > 0);
	struct Link* front = list->frontSentinel->next;
	list->frontSentinel->next = front->next;
	front->next->prev = list->frontSentinel;
	free(front);
	list->size--;
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list != NULL);
	assert(list->size > 0);
	struct Link* back = list->backSentinel->prev;
	list->backSentinel->prev = back->prev;
	back->prev->next = list->backSentinel;
	free(back);
	list->size--;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	assert(list != NULL);
	if (list->size == 0)
		return 1;
	return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	assert(list != NULL);
	assert(list->size > 0);
	struct Link* currentLink = list->frontSentinel->next;
	
	while(currentLink != list->backSentinel)
	{
		if (currentLink->next == list->backSentinel)
			printf("%d\n\n", currentLink->value);
		else
			printf("%d\n", currentLink->value);
		
		currentLink = currentLink->next;
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);
	struct Link* last = list->backSentinel->prev;
	struct Link* newLink = malloc (sizeof(struct Link));
	newLink->value = value;
	last->next = newLink;
	list->backSentinel->prev = newLink;
	newLink->prev = last;
	newLink->next = list->backSentinel;
	list->size++;
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);

	if (list->size == 0)
		return 0;
	
	struct Link* currentLink = list->frontSentinel->next;
	
	while(currentLink != list->backSentinel)
	{
		if (currentLink->value == value)
			return 1;
		currentLink = currentLink->next;
	}
	
	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	int keepLooking = 0;
	
	assert(list != NULL);
	assert(list->size > 0);
	
	struct Link* currentLink = list->frontSentinel->next;
	
	while(keepLooking == 0)
	{
		if (currentLink->value == value)
		{
			struct Link* previous = currentLink->prev;
			previous->next = currentLink->next;
			currentLink->next->prev = previous;
			list->size--;
			free(currentLink);
			keepLooking = 1;
		}
		else
		{
			currentLink = currentLink->next;
			if (currentLink == list->backSentinel)
				keepLooking = 1; // break out of the loop
		}
	}
}
