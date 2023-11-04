// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// size
unsigned int count;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int idx = hash(word);
    node *cur = table[idx];
    while (cur != NULL)
    {
        if (strcasecmp(cur->word, word) == 0)
            return true;
        else
            cur = cur->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
        return false;
    count = 0;
    char word[LENGTH + 1];

    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        strcpy(table[i]->word, "");
        table[i]->next = NULL;
    }
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
            return false;
        strcpy(n->word, word);
        n->next = NULL;

        int idx = hash(n->word);

        n->next = table[idx]->next;
        table[idx]->next = n;

        count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];
        while (temp != NULL)
        {
            node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    return true;
}
