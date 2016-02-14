#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "stdlib.h"
#include "string.h"
#include <stdbool.h>

#define TABLE_LENGTH 100

/*For Linked List*/
typedef struct list_node{
    char *value;
    struct list_node* next;
} list_node;

typedef struct symbol_table{
    list_node* table[TABLE_LENGTH];
} symbol_table;

/* ----------Function Declaration---------- */
unsigned int generate_RSHash(char* , unsigned int);
bool insert_hash(symbol_table*, char*);
void print_hash_table(symbol_table*);
void delete_hash_table(symbol_table*);

#endif //HASHTABLE_H
