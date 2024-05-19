// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char tmp[LENGTH + 1];
    strcpy(tmp, word);
    for (int i = 0, num = strlen(tmp); i < num; i++)
    {
        tmp[i] = tolower(tmp[i]);
    }

    for (node *n = table[hash(tmp)]->next; n != NULL; n = n->next)
    {
        if (strcmp(n->word, tmp) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int h = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isalpha(word[i]))
        {
            h += tolower(word[i]);
        }
        h += word[i];
    }

    return h % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *fptr = fopen(dictionary, "r");
    if (fptr == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        if (table[i] == NULL)
        {
            return false;
        }
        table[i]->next = NULL;
    }

    char word[LENGTH + 1];
    while (fscanf(fptr, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        for (int i = 0, num = strlen(n->word); i < num; i++)
        {
            n->word[i] = tolower(n->word[i]);
        }
        unsigned int h = hash(word);
        n->next = table[h]->next;
        table[h]->next = n;
    }

    fclose(fptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *n = table[i]->next; n != NULL; n = n->next)
        {
            count++;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        for (node *n = table[i]->next; n != NULL;)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }
        free(table[i]);
    }
    return true;
}
