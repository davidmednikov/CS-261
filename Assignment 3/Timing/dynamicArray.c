/*********************************************************************
** Program Filename: Assignment 2 - dynamicArray.c
** Author: David Mednikov
** Date: 10/4/17
** Description: Implement a dynamic array and use it in a stack and bag
** implementation
*********************************************************************/

/*	dynamicArray.c: Dynamic Array implementation. */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dynArray.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};


/* ************************************************************************
Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

param: 	v		pointer to the dynamic array
param:	cap 	capacity of the dynamic array
pre:	v is not null
post:	internal data array can hold cap elements
post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v != 0);
	v->data = (TYPE *)malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;
}

/* Allocate and initialize dynamic array.

param:	cap 	desired capacity for the dyn array
pre:	none
post:	none
ret:	a non-null pointer to a dynArr of cap capacity
and 0 elements in it.
*/
DynArr* newDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof(struct DynArr));
	assert(r != 0);
	initDynArr(r, cap);
	return r;
}

/* Deallocate data array in dynamic array.

param: 	v		pointer to the dynamic array
pre:	none
post:	d.data points to null
post:	size and capacity are 0
post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if (v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure.

param: 	v		pointer to the dynamic array
pre:	none
post:	the memory used by v->data is freed
post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap

param: 	v		pointer to the dynamic array
param:	cap		the new desired capacity
pre:	v is not null
post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{
	assert(v != NULL); // v is not null
	DynArr newArray; // create new array
	initDynArr(&newArray, newCap); // initialize new array with provided capacity

	for (int i = 0; i < v->size; i++) // loop through old array
		addDynArr(&newArray, v->data[i]); // copy values from old array to new array
		
	freeDynArr(v); // clear old array's allocated memoey

	*v = newArray; // point v to new array with new capacity
}

/* Get the size of the dynamic array

param: 	v		pointer to the dynamic array
pre:	v is not null
post:	none
ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

param: 	v		pointer to the dynamic array
param:	val		the value to add to the end of the dynamic array
pre:	the dynArry is not null
post:	size increases by 1
post:	if reached capacity, capacity is doubled
post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{
	assert(v->data != NULL); // dynamic array is not null

	if (v->size == v->capacity) // if array is full
	{
		_dynArrSetCapacity(v, v->capacity * 2); // double capacity of array
	}

	v->data[v->size] = val; // add new value to array
	v->size++; // increment size by 1

}

/*	Get an element from the dynamic array from a specified position

param: 	v		pointer to the dynamic array
param:	pos		integer index to get the element from
pre:	v is not null
pre:	v is not empty
pre:	pos < size of the dyn array and >= 0
post:	no changes to the dyn Array
ret:	value stored at index pos
*/

TYPE getDynArr(DynArr *v, int pos)
{
	assert(v != NULL); // v is not null
	assert(v->size > 0); // v is not empty
	assert(pos < v->size); // position is less than size
	assert(pos >= 0); // index is not negative

	return v->data[pos]; // return value at pos
}

/*	Put an item into the dynamic array at the specified location,
overwriting the element that was there

param: 	v		pointer to the dynamic array
param:	pos		the index to put the value into
param:	val		the value to insert
pre:	v is not null
pre:	v is not empty
pre:	pos >= 0 and pos < size of the array
post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	assert(v != NULL); // v is not null
	assert(v->size > 0); // v is not empty
	assert(pos < v->size); // position is less than size
	assert(pos >= 0); // index is not negative

	v->data[pos] = val; // store value to specified index
}

/*	Swap two specified elements in the dynamic array

param: 	v		pointer to the dynamic array
param:	i,j		the elements to be swapped
pre:	v is not null
pre:	v is not empty
pre:	i, j >= 0 and i,j < size of the dynamic array
post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{
	int temp; // temp variable for swap

	assert(v != NULL); // v is not null
	assert(v->size > 0);// v is not empty
	assert(i < v->size); // 1st position is less than size
	assert(j < v->size); // 2nd position is less than size
	assert(i >= 0); // 1st position is not negative
	assert(j >= 0); // 2nd position is not negative

	temp = v->data[i]; // hold value at i in temp variable
	v->data[i] = v->data[j]; // copy value from j to i
	v->data[j] = temp; // copy temp value to j
}

/*	Remove the element at the specified location from the array,
shifts other elements back one to fill the gap

param: 	v		pointer to the dynamic array
param:	idx		location of element to remove
pre:	v is not null
pre:	v is not empty
pre:	idx < size and idx >= 0
post:	the element at idx is removed
post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{
	assert(v != NULL);  // v is not null
	assert(v->size > 0);  // v is not empty
	assert(idx < v->size);  // index is less than size
	assert(idx >= 0); // index is not negative

	for (int i = idx; i < v->size - 1; i++) // loop through elements after deletion
	{
		v->data[i] = v->data[i + 1]; // move values one element to the left
	}

	v->size--; // decrement size by 1
}



/* ************************************************************************
Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the
dynamic array stack has an item on it.

param:	v		pointer to the dynamic array
pre:	the dynArr is not null
post:	none
ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v)
{
	assert(v->data != NULL); // array is not null

	if (v->size > 0) // if not empty, return 0
		return 0;
	else // if empty, return 1
		return 1;
}

/* 	Push an element onto the top of the stack

param:	v		pointer to the dynamic array
param:	val		the value to push onto the stack
pre:	v is not null
post:	size increases by 1
if reached capacity, capacity is doubled
val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{
	assert(v != NULL); // v is not null

	if (v->size == v->capacity) // if array is full capacity needs to be doubled
	{
		_dynArrSetCapacity(v, v->capacity * 2); // double capacity of array
	}

	v->data[v->size] = val; // add value to stack
	v->size++; // increment size by 1

}

/*	Returns the element at the top of the stack

param:	v		pointer to the dynamic array
pre:	v is not null
pre:	v is not empty
post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{
	assert(v != NULL); // v is not null
	assert(v->size > 0); // v is not empty

	return v->data[v->size - 1]; // get value at top of stack
}

/* Removes the element on top of the stack

param:	v		pointer to the dynamic array
pre:	v is not null
pre:	v is not empty
post:	size is decremented by 1
the top has been removed
*/
void popDynArr(DynArr *v)
{
	assert(v != NULL); // v is not null
	assert(v->size > 0); // v is not empty

	v->size--; // decrement size by 1
}

/* ************************************************************************
Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
the specified value is in the collection
true = 1
false = 0

param:	v		pointer to the dynamic array
param:	val		the value to look for in the bag
pre:	v is not null
pre:	v is not empty
post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{
	assert(v != NULL); // v is not null
	assert(v->size > 0); // v is not empty

	for (int i = 0; i < v->size; i++) // loop through array
	{
		if (val == v->data[i]) // if value is found in array
			return 1; // true
	}

	return 0; // false

}

/*	Removes the first occurrence of the specified value from the collection
if it occurs

param:	v		pointer to the dynamic array
param:	val		the value to remove from the array
pre:	v is not null
pre:	v is not empty
post:	val has been removed
post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val)
{
	int found = 0; // value not found (yet)
	int foundIndex; // where value was found
	int currentIndex = 0; // iterator for while loop

	assert(v != NULL); // v is not null
	assert(v->size > 0); // v is not empty

	while (found == 0) // while value has not been found
	{
		if (val == v->data[currentIndex]) // if value matches current index
		{
			foundIndex = currentIndex; // keep track of found index
			found = 1; // found is true, break out of while loop
		}
		else
			currentIndex++; // if no match then increase index by 1
	}

	if (found == 0) // not found
		printf("\nThis item isn't in the bag!\n");
	else // found
	{
		for (int i = foundIndex; i < v->size - 1; i++) // loop from foundIndex to end of array
			v->data[i] = v->data[i + 1]; // move elements left 1 spot

		v->size--; // decrement size by 1
	}
}
