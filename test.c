// #define _GNU_SOURCE
// #include <stdio.h>//
// #include <stdlib.h>
// #include <stdbool.h> //
// #include <ctype.h>//

// #define DICTIONARY "text.txt"

// #define LENGTH 45

// // Represents a node in a hash table
// typedef struct node
// {
//     char word[LENGTH + 1];
//     struct node *next;
// }
// node;

// // TODO: Choose number of buckets in hash table
// const unsigned int N = 26;

// // Hash tabledictionary
// node *table[N];

// unsigned int hash(const char *word);

// bool load(const char *dictionary);

// void print_file(node *cp);

// void free_p(node *n);


// int main(int argc, char *argv[])
// {
//     load(DICTIONARY);

//     return 0;
// }

// bool load(const char *dictionary)
// {
//     // open dictionary
//     FILE *fp = fopen(dictionary, "r");
//     if (fp == NULL)
//     {
//         return false;
//     }

//     // argument for reading
//     char *line = NULL;
//     size_t len = 0;
//     ssize_t read;

//     // read line by line
//     while ((read = getline(&line, &len, fp)) != -1)
//     {
//         // terminate string
//         line[read - 1] = '\0';

//         // compute has code
//         int code = hash(line);

//         // allocate space from new node
//         node *new = malloc(sizeof(node));
//         if (new == NULL)
//         {
//             return false;
//         }

//         // fill up and link to list
//         for (int i = 0; i < read; i++)
//         {
//             new->word[i] = line[i];
//         }
//         new->next = table[code];
//         table[code] = new;
//     }

//     return true;
// }

// unsigned int hash(const char *word)
// {
//     return tolower(word[0]) - 'a';
// }

#include <stdio.h>

int main(void){

    int q = 1, f = 2;

    int *a[2];
    a[0] = &q;
    a[1] = &f;

    free(a);
}