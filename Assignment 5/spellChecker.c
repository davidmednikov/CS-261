/*
* CS 261 Data Structures
* Assignment 5
* File: spellChecker.c
* Name: David Mednikov
* Date: 11/15/17
*/

#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
* Loads the contents of the file into the hash map.
* @param file
* @param map
*/
void loadDictionary(FILE* file, HashMap* map)
{	
	char* key = nextWord(file); // get first word

	while (key != NULL) // read file one word at a time
	{
		hashMapPut(map, key, 1); // place word into hash table

		free(key); // free word from memory
		key = nextWord(file); // get next word
	}
}



/**
* Calculates the Levenshtein Distance between two strings
* @param string 1
* @param length of string 1
* @param string 2
* @param length of string 2
* @return int
* used https://www.lemoda.net/c/levenshtein/ as reference, but made my own modifications
*/
int levenshteinDistance(const char * word1, int len1, const char * word2, int len2)
{
	int rows = len1 + 1; // create matrix
	int columns = len2 + 1;
	
	/* dynamically allocate memory for matrix */
	int** matrix = (int**)malloc(rows * sizeof(int*));
	
	for (int i = 0; i < rows; i++)
		matrix[i] = (int*)malloc(columns * sizeof(int*));

	/* initialize matrix */
	int i;
	
	for (i = 0; i <= len1; i++)
		matrix[i][0] = i;
	
	for (i = 0; i <= len2; i++)
		matrix[0][i] = i;
	
	/* find distance between two words */
	for (i = 1; i <= len1; i++) 
	{
		int j;
		char c1;

		c1 = word1[i - 1];
		
		for (j = 1; j <= len2; j++) 
		{
			char c2;

			c2 = word2[j - 1];
			
			if (c1 == c2)
				matrix[i][j] = matrix[i - 1][j - 1];
			
			else 
			{
				int delete;
				int insert;
				int substitute;
				int minimum;

				delete = matrix[i - 1][j] + 1;
				insert = matrix[i][j - 1] + 1;
				substitute = matrix[i - 1][j - 1] + 1;
				minimum = delete;
				
				if (insert < minimum) 
					minimum = insert;
				
				if (substitute < minimum) 
					minimum = substitute;
				
				matrix[i][j] = minimum;
			}
		}
	}
	
	int distance = matrix[len1][len2]; // copy distance from array to int variable

	/* remove dynamic arrays from memory */
	for (int i = 0; i < rows; i++)
		free(matrix[i]);

	free(matrix);

	// return calculated distance
	return distance;
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
	HashMap* map = hashMapNew(100);

	FILE* file = fopen("dictionary.txt", "r");

	clock_t timer = clock();
	loadDictionary(file, map);
	timer = clock() - timer;
	printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	fclose(file);

	char inputBuffer[256];
	int quit = 0;
	while (!quit)
	{
		printf("\nEnter a word or \"quit\" to quit: ");
		scanf("%s", inputBuffer);

		// Implement the spell checker code here..

		if (strcmp(inputBuffer, "quit") == 0) // if user entered quit, exit the program
			quit = 1;

		else // search for input
		{
			if (hashMapContainsKey(map, inputBuffer)) // if word is already in dictionary
				printf("\nThe word was spelled correctly.\n");

			else // misspelled world
			{
				int closeMatches = 0; // keep track of how many close matches we have
				char* matches[6]; // array of strings to store closest matches

				for (int i = 0; i < 6; i++) // initialize array
					matches[i] = NULL;

				int closeness = 1; // start looking for words that are only off by 1 letter
				
				while (closeMatches < 6) // while there rae less than 6 matches
				{
					for (int i = 0; i < map->capacity; i++) // loop through buckets
					{
						HashLink* iterator = map->table[i]; // point iterator to first link in bucket

						while (iterator != NULL && closeMatches < 6) // traverse list until the iterator is null or 6 close matches have been found
						{
							char* compare = iterator->key; // get word to compare to input
							int similarity = levenshteinDistance(inputBuffer, strlen(inputBuffer), compare, strlen(compare)); // find distance between input and word in dictionary

							if (similarity == closeness) // if the similarity matches the specified "closeness"
							{
								matches[closeMatches] = iterator->key; // add the word to the array of close matches
								closeMatches++; // increment close matches by 1
							}

							iterator = iterator->next; // iterate to next link
						}
					}

					closeness++; // if there are still less than 6 matches after checking the entire table, increaes the allowable distance between input and matches by 1 letter
				}

				for (int i = 0; i < closeMatches; i++) // loop through array of matches, suggesting them to the user
					printf("\nDid you mean %s?", matches[i]);

				printf("\n");
			}
		}
	}

	hashMapDelete(map);
	return 0;
}