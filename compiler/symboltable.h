#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define TABLE_LENGTH 100

typedef struct list_node  {
	char *value;
	struct list_node *next;
} list_node;

typedef struct symbol_table  {
	list_node* table[TABLE_LENGTH];	
} symbol_table;

/* Symbol table management routines */
void init_symtab();
void print_symtab();
void cleanup_symtab();
void insert_id(char *text);

/* Comment table management routines */
void init_comtab();
void print_comtab();
void cleanup_comtab();
void insert_comment(char *comment);


/* generate the hash function */
unsigned int generate_RSHash(char *str, unsigned int len);

#endif //SYMBOLTABLE_H
