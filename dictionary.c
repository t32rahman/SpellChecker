// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
k
// Number of buckets in hash table
const unsigned int N = 101; // prime number finite field



// Hash table
node *table[N];
int sizeofdic = 0; // size of diction (number of words)
bool loaded = false;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int h = 0;
    node *n;
    char lword[strlen(word)];

    strcpy(lword, word);

    for (int i = 0; lword[i] != '\0'; i++)
    {
        lword[i] = tolower(lword[i]);
    }

    h = hash(lword);

    if (table[h] != NULL)
    {
        n = table[h];
        while (n != NULL)
        {
            if (strcmp(n->word, lword) == 0)
            {
                return true;
            }

            n = n->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int hashValue = 0;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        hashValue = hashValue + ((int) word[i]);
    }

    hashValue = hashValue % (N - 1);

    return hashValue;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *data = fopen(dictionary, "r");

    node *n;
    char word[LENGTH + 1];
    int h = 0;
    if (data != NULL)
    {
        while (fscanf(data, "%s", word) != EOF)
        {

            n = malloc(sizeof(node));

            if (n == NULL)
            {
                free(n);
                return false;
            }

            strcpy(n->word, word);

            h = hash(word);

            n->next = table[h];
            table[h] = n;
            sizeofdic++;
        }

        fclose(data);
        loaded = true;
        return true;
    }

    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (loaded == false)
    {
        return 0;
    }
    else
    {
        return sizeofdic;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *tmp, *cursor;

    if (loaded == false)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            cursor = table[i];
            while (cursor != NULL)
            {
                tmp = cursor;
                cursor = cursor->next;

                free(tmp);
            }
        }
    }

    return true;
}
