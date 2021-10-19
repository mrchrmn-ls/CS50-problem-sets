// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 99991;

// Hash table
node *table[N];

// Dictionary word count
unsigned int dsize = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(dict, "%s", word) != EOF)
    {
        // Create and initialize new node for word from dictionary
        node *insert = malloc(sizeof(node));
        strcpy(insert->word, word);
        insert->next = NULL;

        // Find index in hash table for new word
        unsigned int index = hash(word);

        // Insert new node into linked list at index
        insert->next = table[index];
        table[index] = insert;

        //printf("%s\n", word);

        // Add to word count of dictionary
        dsize++;
    }

    fclose(dict);

    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int value = 1;
    for (int i = 0; i < strlen(word); i++)
    {
        if (i < 6)
        {
            value = value * tolower(word[i]);
        }
        else
        {
            value = value + tolower(word[i]);
        }
    }
    //printf("%i\n", value % N);
    return value % N;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dsize;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index = hash(word);

    if (table[index] == NULL)
    {
        return false;
    }
    else
    {
        node *cursor = table[index];

        while (cursor != NULL)
        {
            if (strcasecmp(word, cursor->word) == 0)
            {
                return true;
            }

            cursor = cursor->next;
        }

        return false;

    }

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *cursor = table[i];
            node *tmp = cursor;

            while (cursor != NULL)
            {
                cursor = cursor->next;
                free(tmp);
                tmp = cursor;
            }
        }
    }
    return true;
}

