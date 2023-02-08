// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = (LENGTH + 1) * ('z');

// Declare variable
int total_words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get a hash index from word
    int index = hash(word);

    // Point cursor to the first node
    node *cursor = table[index];

    // Traverse the linked list to find the word
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        // If not founded then point to next
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        sum += tolower(word[i]);
    }
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE *dict = fopen(dictionary, "r");

    if (dict == false)
    {
        return false;
    }

    // Read strings from file one at time, this dword is a buffer.
    char dword[LENGTH + 1];

    while (fscanf(dict, "%s", dword) != EOF)
    {
        // Reading words
        // Create a node for each word
        node *w = malloc(sizeof(node));

        // If malloc failed return false.
        if (w == NULL)
        {
            return false;
        }

        // Copy the word to the node, to tranform the date type.
        strcpy(w->word, dword);
        w->next = NULL;

        // Hash the woerd to obtain hash index.
        int index = hash(dword);

        if (table[index] == NULL)
        {
            table[index] = w;
        }
        else
        {
            // Avoid to let table pointer w first because it will let other node be an orphan.
            w->next = table[index];
            table[index] = w;
        }

        total_words++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return total_words;
}
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through the buckets in the hash table
    for (int i = 0; i < N; i++)
    {
        // Point first table buckets
        node *head = table[i];
        node *cursor = head;
        node *temp = head;

        // Use free(cursor) to free the linked list
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }

    return true;
}
