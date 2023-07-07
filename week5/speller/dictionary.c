// Implements a dictionary's functionality
#define _GNU_SOURCE
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// int for number of words in dictionary
int NWD = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// free row
void freeDictionary(node *n);

// TODO: Choose number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // find row with right hash word
    node *colum = table[hash(word)];

    // if there is something
    while (colum != NULL)
    {
        // chech if it is the same
        if (!strcasecmp(colum->word, word))
        {
            return true;
        }
        // else continue
        else
        {
            colum = colum->next;
        }
    }

    // if there is not same word
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // // TODO: Improve this hash function
    int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ tolower(word[i]);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        return false;
    }

    // buffer for word
    char buffer[LENGTH + 1];

    // read word by word
    while (fscanf(fp, "%s", buffer) != EOF)
    {
        // allocate space
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return false;
        }

        // hash given word
        int code = hash(buffer);

        // copy word from buffer into node
        strcpy(new->word, buffer);

        // link to right link list
        new->next = table[code];
        table[code] = new;

        // track number of words
        size();
    }

    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // number of words in dictionary
    return NWD++;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // for each hash code
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            freeDictionary(table[i]);
        }
    }
    return true;
}

void freeDictionary(node *n)
{
    // TODO: Handle base case
    if (n->next != NULL)
    {
        freeDictionary(n->next);
    }

    free(n);
}