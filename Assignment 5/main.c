/*
* CS 261 Data Structures
* Assignment 5
* File: main.c
* Name: David Mednikov
* Date: 11/15/17
*/

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    // --- Concordance code begins here ---
    
	FILE *inputFile = fopen(fileName, "r"); // open file
	
	char* key = nextWord(inputFile); // get first word
	
	while (key != NULL) // read file one word at a time
	{
		if (!hashMapContainsKey(map, key)) // if word is not in table, add as a new link
			 hashMapPut(map, key, 1);
			 
		else // word already in table
		{
			int* occurence = hashMapGet(map,key); // get pointer to number of times word appears
			
			(*occurence)++; // incremement occurence by 1
		}
		
		free(key); // free word from memoru
		key = nextWord(inputFile); // get next word
	}
	
	fclose(inputFile); // close file when done
	
	for (int i = 0; i < map->capacity; i++) // loop through buckets
	{
		HashLink* iterator = map->table[i]; // iterator
		
		while (iterator != NULL) // while traversing list
		{
			printf("\n%s: %d", iterator->key, iterator->value); // print current link's key and value
			iterator = iterator->next; // iterate to next link
		}
	}
	
	printf("\n");
	
    // --- Concordance code ends here ---
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}