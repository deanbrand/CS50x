// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    // Make a cursor node which points to the head of the hash table
    node *cursor = table[index];

    // Loop to go through the list until the final node is reached
    for (node *temp = cursor; temp != NULL; temp = temp->next)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Get the lengh of the string then sum the value of the characters
    unsigned int hashvalue = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        hashvalue += tolower(word[i]);
        hashvalue = (hashvalue * tolower(word[i])) % N;
    }
    return hashvalue;
    // return toupper(word[0]) - 'A';
}

int counter = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // This function returns true if all data loaded into hash table, false if there is an error
    // Stores all data in a hash table, the hash function assigns an index to each word
    // First, to add new data to hash table, allocate memory for nodes then add data to the node
    // This format copies words into the character array strcpy(n->word, "hello"); to set next pointer n->next = NULL;

    // Open dictionary file and read the contents
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error - Empty file");
        return false;
    }

    // Wordlist is a character array of the words.
    char wordlist[LENGTH + 1];

    // While fscanf != EOF print the words into the character array word
    while (fscanf(file, "%s", wordlist) != EOF)
    {
        // Keep track of how many nodes are being made
        counter++;

        // For each new node allocate memory.
        node *newNode = malloc(sizeof(node));

        // Check for null
        if (newNode == NULL)
        {
            return 1;
        }

        // Initialize the new node by copying the word to the next node
        strcpy(newNode->word, wordlist);
        newNode->next = NULL;

        // Add to hash table each element of the hashtable is a linked list
        // If index != NULL newNode->word points to the old head of the list
        int index = hash(wordlist);

        // If the index is not yet assigned, put the newest node at the head of this index
        if (table[index] == NULL)
        {
            table[index] = newNode;
        }

        // If the index is assigned point the existing head node at the table[index] and then make the new node the head
        else
        {
            // Makes the next the new head
            newNode->next = table[index];

            // Head points to the new node
            table[index] = newNode;
        }
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Count how many nodes have been added
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // For each of hash table 'buckets' the memory must be freed
    // Make a cursor which points to the head node.
    // This cursor will work through the linked lists making each = NULL, freeing the memory

    node *tmp = NULL;
    node *cursor = NULL;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}