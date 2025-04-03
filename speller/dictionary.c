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

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int pos = hash(word);
    node *pointer = table[pos];
    for (node *tmp = pointer; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

unsigned int hash(const char *word)
{
    unsigned int value = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        value += tolower(word[i]);
        value = (value * tolower(word[i])) % N;
    }
    return value;
}

int counter = 0;
// Loads dictionary into memory, returning true if successful, else false

bool load(const char *dictionary)
{

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Something went wrong");
        return false;
    }

    char list[LENGTH + 1];

    while (fscanf(dict, "%s", list) != EOF)
    {

        counter++;

        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            return 1;
        }

        strcpy(new_node->word, list);
        new_node->next = NULL;

        int pos = hash(list);

        if (table[pos] == NULL)
        {
            table[pos] = new_node;
        }

        else
        {

            new_node->next = table[pos];

            table[pos] = new_node;
        }
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp = NULL;
    node *pointer = NULL;
    for (int i = 0; i < N; i++)
    {
        pointer = table[i];
        while (pointer != NULL)
        {
            tmp = pointer;
            pointer = pointer->next;
            free(tmp);
        }
    }
    return true;
}
