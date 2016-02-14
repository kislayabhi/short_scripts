#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "symboltable.h"


/* Globally declare a symbol table pointer*/
symbol_table *my_table;
symbol_table *my_comments;

void init_symtab()  {	/* Initialize Symbol Table */
	my_table = malloc(sizeof(symbol_table));
}

void insert_id(char *text)  {	/* Populate Symbol Table */
	
	list_node *new_node = malloc(sizeof(list_node));
	new_node->value = malloc(sizeof(text));
	
	unsigned int hash_value = generate_RSHash(text, strlen(text));
	
	/* We keep the array size of TABLE_LENGTH. */
	unsigned int table_index = hash_value % TABLE_LENGTH;
	
	if(!my_table->table[table_index]) {  	/* Initial case */
		my_table->table[table_index] = new_node;
		strcpy(new_node->value, text);
		new_node->next = NULL;
	}
	else  {
		bool collision = false;
		list_node *node;
		for(node = my_table->table[table_index]; node->next != NULL;
			       	node = node->next)	
			if(strcmp(node->value, text) == 0)  {
				strcpy(node->value, text);
				collision = true;
				break;
		    	}
		if(collision == false)  {
		    /* Otherwise we add the new hash value at the last */  
		    strcpy(new_node->value, text);
		    new_node->next = NULL;
		    node->next = new_node;
		}
	}
}

void print_symtab()  {	/* Print Symbol Table */

	for(int i = 0; i < TABLE_LENGTH; i++)
		if(my_table->table[i])  {
			printf("id: %d \n", i);	
			list_node *start=my_table->table[i];
			for(; start!=NULL; start = start->next)
				printf("\t %s\n", start->value);
		}
}

void cleanup_symtab()  {  /* Clean Symbol Table */

    for(int i=0; i<TABLE_LENGTH; i++)
        if(my_table->table[i])  {
            list_node* temp1 = my_table->table[i];
            list_node* temp2;
            while(temp1)  {
                temp2 = temp1->next;
                free(temp2->value);
		free(temp1);
                temp1 = temp2;
            }
            my_table->table[i] = NULL;
        }
    free(my_table);
}

void init_comtab()	/* Initialize Comment Table */
{
	my_comments = malloc(sizeof(symbol_table));
}

void insert_comment(char *comment)  /* Insert comments into Comment Table */
{

	list_node *new_node = malloc(sizeof(list_node));
	new_node->value = malloc(sizeof(comment));
	
	unsigned int hash_value = generate_RSHash(comment, strlen(comment));
	
	/* We keep the array size of TABLE_LENGTH. */
	unsigned int table_index = hash_value % TABLE_LENGTH;
	
	if(!my_comments->table[table_index]) {  	/* Initial case */
		my_comments->table[table_index] = new_node;
		strcpy(new_node->value, comment);
		new_node->next = NULL;
	}
	else  {
		bool collision = false;
		list_node *node;
		for(node = my_comments->table[table_index]; node->next != NULL;
			       	node = node->next)	
			if(strcmp(node->value, comment) == 0)  {
				strcpy(node->value, comment);
				collision = true;
				break;
		    	}
		if(collision == false)  {
		    /* Otherwise we add the new hash value at the last */  
		    strcpy(new_node->value, comment);
		    new_node->next = NULL;
		    node->next = new_node;
		}
	}
}

void print_comtab()	/* Print Comment Table */
{
	for(int i = 0; i < TABLE_LENGTH; i++)
		if(my_comments->table[i])  {
			printf("com: %d \n", i);	
			list_node *start = my_comments->table[i];
			for(; start != NULL; start = start->next)
				printf("\t %s\n", start->value);
		}
}

void cleanup_comtab()	/* Clean Comment Table */
{
	for(int i=0; i<TABLE_LENGTH; i++)
		if(my_comments->table[i])  {
			list_node* temp1 = my_comments->table[i];
			list_node* temp2;
			while(temp1)  {
				temp2 = temp1->next;
				free(temp1->value);
				free(temp1);
				temp1 = temp2;
			}
			my_comments->table[i] = NULL;
		}
		free(my_comments);
}

unsigned int generate_RSHash(char* str, unsigned int len)  {
	unsigned int b    = 378551;
	unsigned int a    = 63689;
	unsigned int hash = 0;
	unsigned int i    = 0;

	for(i = 0; i < len; str++, i++)  {
		hash = hash * a + (*str);
		a = a * b;
	}
	return hash;
}
/* End Of RS Hash Function */
