#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "symboltable.h"
#include "hash_table.h"


/* Globally declare a symbol table pointer */
symbol_table *id_table;
symbol_table *comment_table;

void init_symtab()  {	/* Initialize Symbol Table */
	id_table = (symbol_table*)malloc(sizeof(symbol_table));
	id_table->size = 0;
}

void insert_id(char *text)  {  /* Populate Symbol Table */
	insert_hash(id_table, text);
}

void print_symtab()  {  /* Print Symbol Table */
	printf("\n\nFrequency of identifiers");
	print_hash_table(id_table, true);
}

void cleanup_symtab()  {  /* Clean Symbol Table */
	delete_hash_table(id_table);
}

void init_comtab()  {  /* Initialize Comment Table */
	comment_table = (symbol_table*)malloc(sizeof(symbol_table));
	comment_table->size = 0;
}

void insert_comment(char *comment)  {  /* Insert comments into Comment Table */
	insert_hash( comment_table, comment);
}

void print_comtab()  {  /* Print Comment Table */
	print_hash_table(comment_table, false);
}

void cleanup_comtab()  {  /* Clean Comment Table */
	delete_hash_table(comment_table);
}
