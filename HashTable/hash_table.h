#include "stdlib.h"
#include "string.h"
#include <stdbool.h>


/*For Linked List*/
typedef struct list_node{
    char* value;
    struct list_node* next;
} list_node;

typedef struct symbol_table{
    list_node* table[100];
} symbol_table;


/* ----------Function Declaration---------- */
unsigned int generate_RSHash(char* , unsigned int);
bool insert_hash(char*);
void print_hash_table();
void print_till_end(list_node*);
void delete_hash_table();
