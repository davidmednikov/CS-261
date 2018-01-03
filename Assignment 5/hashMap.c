/*
* CS 261 Data Structures
* Assignment 5
* File: hashMap.c
* Name: David Mednikov
* Date: 11/15/17
*/

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int hashFunction1(const char* key)
{
	int r = 0;
	for (int i = 0; key[i] != '\0'; i++)
	{
		r += key[i];
	}
	return r;
}

/****
*
* In order to make my hash table (for spell check only) as well-spaced as possible, I modified this hash function, which increased the spacing and efficiency tremendously
*
****/
int hashFunction2(const char* key)
{
	int r = 0;
	for (int i = 0; key[i] != '\0'; i++)
	{                        /* key[i] was not here before */
		r += (i + 1) * key[i] * key[i];
 // was r += (i + 1) * key[i];
	}
	return r;
}

/**
* Creates a new hash table link with a copy of the key string.
* @param key Key string to copy in the link.
* @param value Value to set in the link.
* @param next Pointer to set as the link's next.
* @return Hash table link allocated on the heap.
*/
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
	HashLink* link = malloc(sizeof(HashLink));
	link->key = malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(link->key, key);
	link->value = value;
	link->next = next;
	return link;
}

/**
* Free the allocated memory for a hash table link created with hashLinkNew.
* @param link
*/
static void hashLinkDelete(HashLink* link)
{
	free(link->key);
	free(link);
}

/**
* Initializes a hash table map, allocating memory for a link pointer table with
* the given number of buckets.
* @param map
* @param capacity The number of table buckets.
*/
void hashMapInit(HashMap* map, int capacity)
{
	map->capacity = capacity;
	map->size = 0;
	map->table = malloc(sizeof(HashLink*) * capacity);
	for (int i = 0; i < capacity; i++)
	{
		map->table[i] = NULL;
	}
}

/**
* Removes all links in the map and frees all allocated memory. You can use
* hashLinkDelete to free the links.
* @param map
*/
void hashMapCleanUp(HashMap* map)
{
	for (int i = 0; i < map->capacity; i++) // loop through buckets
	{
		HashLink *iterator = map->table[i]; // create iterator pointer

		while (iterator != NULL) // traverse list
		{
			HashLink *temp = iterator; // temp pointer for current link for deletion
			iterator = iterator->next; // iterate to next link
			hashLinkDelete(temp); // delete link pointed to by temp
		}
	}
	
	free(map->table); // free array of pointers
}

/**
* Creates a hash table map, allocating memory for a link pointer table with
* the given number of buckets.
* @param capacity The number of buckets.
* @return The allocated map.
*/
HashMap* hashMapNew(int capacity)
{
	HashMap* map = malloc(sizeof(HashMap));
	hashMapInit(map, capacity);
	return map;
}

/**
* Removes all links in the map and frees all allocated memory, including the
* map itself.
* @param map
*/
void hashMapDelete(HashMap* map)
{
	hashMapCleanUp(map);
	free(map);
}

/**
* Returns a pointer to the value of the link with the given key. Returns NULL
* if no link with that key is in the table.
*
* Use HASH_FUNCTION(key) and the map's capacity to find the index of the
* correct linked list bucket. Also make sure to search the entire list.
*
* @param map
* @param key
* @return Link value or NULL if no matching link.
*/
int* hashMapGet(HashMap* map, const char* key)
{
	int index = HASH_FUNCTION(key) % (map->capacity); // get hash index

	HashLink *iterator = map->table[index]; // create iterator at index

	while (iterator != NULL) // traverse list
	{
		if (strcmp(key, iterator->key) == 0) // current link contains key
			return &(iterator->value); // return pointer to int

		iterator = iterator->next; // iterate to next link
	}

	return NULL; // matching key not found, return NULL
}

/**
* Resizes the hash table to have a number of buckets equal to the given
* capacity. After allocating the new table, all of the links need to be
* rehashed into it because the capacity has changed.
*
* Remember to free the old table and any old links if you use hashMapPut to
* rehash them.
*
* @param map
* @param capacity The new number of buckets.
*/
void resizeTable(HashMap* map, int capacity)
{
	HashLink** resized = malloc(sizeof(HashLink*) * capacity); // create new hash map
	for (int i = 0; i < capacity; i++) // initialize links
	{
		resized[i] = NULL;
	}

	for (int i = 0; i < map->capacity; i++)
	{
		HashLink *iterator = map->table[i]; // create iterator pointer

		while (iterator != NULL) // traverse list
		{
			int index = HASH_FUNCTION(iterator->key) % (capacity); // get hash index

			if (index < 0) // negative hash index, add size to loop around
				index += capacity;

			HashLink *resizedItr = resized[index]; // create iterator at index
			HashLink *previous = NULL;

			while (resizedItr != NULL) // traverse list
			{
				previous = resizedItr; // assign previous
				resizedItr = resizedItr->next; // go until reaching null pointer
			}

			char* key = iterator->key; // get key and value of current link
			int val = iterator->value;

			HashLink *newLink = hashLinkNew(key, val, NULL); // create new link using key and value

			if (previous == NULL) // first link
				resized[index] = newLink; // add to head of bucket list
			else // not first link, add after previous
				previous->next = newLink; // assign link to current iterator

			iterator = iterator->next; // iterate to next link
		}
	}

	hashMapCleanUp(map); // clean up hash table
	map->capacity = map->capacity * 2; // double capacity
	map->table = resized; // point map to resized table
}

/**
* Updates the given key-value pair in the hash table. If a link with the given
* key already exists, this will just update the value. Otherwise, it will
* create a new link with the given key and value and add it to the table
* bucket's linked list. You can use hashLinkNew to create the link.
*
* Use HASH_FUNCTION(key) and the map's capacity to find the index of the
* correct linked list bucket. Also make sure to search the entire list.
*
* @param map
* @param key
* @param value
*/
void hashMapPut(HashMap* map, const char* key, int value)
{
	int index = HASH_FUNCTION(key) % (map->capacity); // get hash index

	if (index < 0) // negative hash index, add size to loop around
		index += map->capacity;

	HashLink *iterator = map->table[index]; // create iterator at index
	HashLink *previous = NULL; // keep track of previous

	while (iterator != NULL) // traverse list
	{
		if (strcmp(key, iterator->key) == 0)// current link contains key
		{
			iterator->value = value; // update value of current link
			return;
		}

		previous = iterator; // update previous
		iterator = iterator->next; // iterate to next link
	}

	HashLink *newLink = hashLinkNew(key, value, NULL); // create new link

	if (previous == NULL)
		map->table[index] = newLink;
	else
		previous->next = newLink; // assign link to current iterator

	map->size++; // increment size

	if (hashMapTableLoad(map) > MAX_TABLE_LOAD) // if max table load is exceeded
		resizeTable(map, map->capacity * 2); // double capacity
}

/**
* Removes and frees the link with the given key from the table. If no such link
* exists, this does nothing. Remember to search the entire linked list at the
* bucket. You can use hashLinkDelete to free the link.
* @param map
* @param key
*/
void hashMapRemove(HashMap* map, const char* key)
{
	int index = HASH_FUNCTION(key) % (map->capacity); // get hash index

	HashLink *iterator = map->table[index]; // create iterator at index
	HashLink *previous = NULL; // keep track of previous

	while (iterator != NULL) // traverse list
	{
		if (strcmp(key, iterator->key) == 0)// current link contains key
		{
			if (previous == NULL) // first element
				map->table[index] = iterator->next; // remove first element
			else
				previous->next = iterator->next; // update links in list

			hashLinkDelete(iterator); // delete current link
			map->size--;
			return;	// leave function
		}

		previous = iterator; // update previous
		iterator = iterator->next; // iterate to next link
	}
}

/**
* Returns 1 if a link with the given key is in the table and 0 otherwise.
*
* Use HASH_FUNCTION(key) and the map's capacity to find the index of the
* correct linked list bucket. Also make sure to search the entire list.
*
* @param map
* @param key
* @return 1 if the key is found, 0 otherwise.
*/
int hashMapContainsKey(HashMap* map, const char* key)
{
	int index = HASH_FUNCTION(key) % (map->capacity); // get hash index

	HashLink *iterator = map->table[index]; // create iterator at index

	while (iterator != NULL) // traverse list
	{
		if (strcmp(key, iterator->key) == 0) // current link contains key
			return 1; // return 1

		iterator = iterator->next; // iterate to next link
	}

	return 0; // matching key not found, return 0
}

/**
* Returns the number of links in the table.
* @param map
* @return Number of links in the table.
*/
int hashMapSize(HashMap* map)
{
	return map->size;
}

/**
* Returns the number of buckets in the table.
* @param map
* @return Number of buckets in the table.
*/
int hashMapCapacity(HashMap* map)
{
	return map->capacity;
}

/**
* Returns the number of table buckets without any links.
* @param map
* @return Number of empty buckets.
*/
int hashMapEmptyBuckets(HashMap* map)
{
	int emptyBuckets = 0; // counter variable

	for (int i = 0; i < map->capacity; i++) // loop through buckets
	{
		if (map->table[i] == NULL) // if pointer is null, bucket is empty
			emptyBuckets++; // increment counter
	}

	return emptyBuckets; // return counter
}

/**
* Returns the ratio of (number of links) / (number of buckets) in the table.
* Remember that the buckets are linked lists, so this ratio tells you nothing
* about the number of empty buckets. Remember also that the load is a floating
* point number, so don't do integer division.
* @param map
* @return Table load.
*/
float hashMapTableLoad(HashMap* map)
{
	double size = (double)map->size; // copy size to floating point number
	double capacity = (double)map->capacity; // copy capacity to floating point number

	float tableLoad = size / capacity;

	return tableLoad; // divide size by capacity
}

/**
* Prints all the links in each of the buckets in the table.
* @param map
*/
void hashMapPrint(HashMap* map)
{
	for (int i = 0; i < map->capacity; i++)
	{
		HashLink* link = map->table[i];
		if (link != NULL)
		{
			printf("\nBucket %i ->", i);
			while (link != NULL)
			{
				printf(" (%s, %d) ->", link->key, link->value);
				link = link->next;
			}
		}
	}
	printf("\n");
}