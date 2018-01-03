/* CS261- Assignment 1 - Q.5*/
/* Name: David Mednikov
 * Date: 10/01/17
 * Solution description: ask the user for a word and change it to StIcKy FoNt.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

/*
sort()
returns: none
params: string (array of chars) word
changes case of letters in word to be WrItTeN UsInG StIcKy FoNt
*/
void sticky(char* word)
{
     int size = strlen(word); // get length of word
     
     for (int i = 0; i < size; i++) // loop through c-string
     {                 
         char ch = word[i]; // save current character to temp variable
         
         if (i == 0 || i % 2 == 0) // if letter's index in word is odd, counting first letter as 1
         {
            if (ch >= 'a' && ch <= 'z') // if lowercase
                word[i] = toUpperCase(ch); // change to uppercase
         }
         else // even index letter
         {
            if (ch >= 'A' && ch <= 'Z') // if uppercase
                word[i] = toLowerCase(ch); // change to lowercase
         }
     }
}

/*
main()
asks the user for a word and changes it so that it LoOkS StIcKy LiKe ThIs
*/
int main()
{
    char word[100]; // c-string for word
    char ogWord[100]; // c-string for copy of word
    
    printf("\nEnter a word, any word! "); // ask user for word
    scanf("%s", word); // get input from user
    
    for (int i = 0; i < strlen(word); i++) // loop through letters of word
        ogWord[i] = word[i]; // copy word to copy variable
        
    sticky(word); // sticky original word
    
    printf("\n%s has been StIcKiEd!\n\n%s\n\n", ogWord, word); // print sticky word
    
    return 0;
}
