/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Prototype declaration
int hash(const char* word);

// Define struct for each word in linked list
typedef struct node 
{
    char word [LENGTH + 1];
    struct node* next;
}
node;

// Define hash table 
node* hashtable[SIZE + 1];

// Keep track of words loaded into dictionary
int word_count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // Pointer to traverse linked list
    node* wordnode;
    
    // Determine hash bucket to traverse
    int hashvalue = hash(word);
    wordnode = hashtable[hashvalue];
    
    // Traverse linked list
    while (wordnode != NULL)
    {
        // Word is found in dictionary
        if (strcasecmp(wordnode->word, word) == 0)
        {
            return true;
        }
        
        // Update pointer to traverse linked list
        wordnode = wordnode->next;
    }
    
    // Word is not in dictionary
    return false;
}   

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{   
    // Open the desired text file requested as dictionary
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not load requested file \n");
        return false;
    }
    
    // Assign all pointers in hash table to NULL
    for (int i = 0; i < SIZE; i ++)
    {
        hashtable[i] = NULL;
    }
    
    // Temporary word storage
    char temp_word[LENGTH + 1];
    
    // Read words into hash table
    while (fscanf(file, "%s", temp_word) != EOF)
    {
        // Create node for each word, check for correct memory usage
        node* new_node = malloc(sizeof(node));
        
        if (new_node == NULL)
        {
            printf("Memory allocation error");
            return false;
        }
        
        // Copy word from temp buffer to linked list
        strcpy(new_node->word, temp_word);
        
        // Returns hash value && assigns to correct bucket
        int hash_function = hash(new_node->word);
    
        // First word into assigned hash bucket
        if (hashtable[hash_function] == NULL)
        {
            hashtable[hash_function] = new_node;
            new_node->next = NULL;
        }
        
        // Hash bucket contains at least one node, add another
        else
        {
            new_node->next = hashtable[hash_function];
            hashtable[hash_function] = new_node;
        }
        
        //  Increase size of dictionary
        word_count++;
    }
    
    // Close file
    fclose(file);
    
    return true; 
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // Dictionary size
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < (SIZE + 1); i++)
    {   
        // Begin with first hash bucket
        node* cursor = hashtable[i];
        
        // Traverse linked list in each bucket, free each node
        while(cursor)
        {
            node* temp  = cursor;
            cursor      = cursor->next;
            free(temp);
        } 
        
        // Free bucket pointer
        hashtable[i] = NULL;  
    }
    
    return true;
}

int hash(const char* word)
{
    //  Covert word to lowercase 
    int len = strlen(word);
    char small_word[len]; 
    small_word[len] = '\0';
    
    for(int i = 0; i < len; i++)
    {
        small_word[i] = tolower(word[i]);
    }
    
    // Hash function assignment
    unsigned int hash = 0;
    for (int i=0, n =strlen(small_word); i<n; i++)
    {
        hash = (hash << 2) ^ small_word[i];
    }
    return hash % SIZE;
}
