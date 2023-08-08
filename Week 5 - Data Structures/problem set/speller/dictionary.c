// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <cs50.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 5023;
unsigned int word_total = 0;

// Prototypes
void unload_helper(node *node);

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get hash value (index) of word
    int index = hash(word);

    // Iterate over nodes in linked list starting at first node at table index
    node *temp = table[index];

    while (temp != NULL)
    {
        // Check whether word match case insensitive
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
        // Move pointer to next node
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // Multiply current value by 27 to reduce collisions
        sum *= 29;
        // Sets ith character of string to int value i.e. 'A' = 1, 'Z' = 26. Apostrophes = 27.
        sum += isalpha(word[i]) ? toupper(word[i]) - 'A' + 1 : 27;
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *infile = fopen(dictionary, "r");

    if (infile == NULL)
    {
        printf("Error opening file!\n");
        return false;
    }

    char buffer[LENGTH + 1];

    // Read each word from infile
    while (fscanf(infile, "%s", buffer) != EOF)
    {
        // Allocate memory for new node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            printf("No memory available for node\n");
            return false;
        }

        // Set node word value
        strcpy(n->word, buffer);

        // Get index of word
        int index = hash(buffer);
        // Add new node to beginning of linked list index

        n->next = table[index];
        table[index] = n;

        // Increment count
        word_total += 1;
    }

    // Close file
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_total;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over eaach bucket in hash table
    for (int i = 0; i < N; i++)
    {
        // Check whether index has node
        if (table[i] != NULL)
        {
            // Call helper function to free nodes
            unload_helper(table[i]);
        }
    }
    return true;
}
// Recursively free nodes
void unload_helper(node *node)
{
    // Keep calling function until end of linked list then start freeing each node
    if (node->next != NULL)
    {
        unload_helper(node->next);
    }
    free(node);
}