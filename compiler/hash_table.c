#include "stdio.h"
#include "hash_table.h"

bool insert_hash(symbol_table *my_table, char *text)  {
	// insert the string at the generated hash.
	list_node *new_node = (list_node*)malloc(sizeof(list_node));
	new_node->value = (char*)malloc(strlen(text)+1);
	new_node->next = NULL;
	//printf("==%s==%d\n", text, strlen(text));

	unsigned int hash_value = generate_RSHash(text, strlen(text));

	/* We keep the array size of TABLE_LENGTH. */
	unsigned int table_index = hash_value % TABLE_LENGTH;

	if(!my_table->table[table_index]) {  	/* Initial case */
		my_table->table[table_index] = new_node;
		strcpy(new_node->value, text);
	}
	else  {
		bool collision = false;
		list_node *node, *prev;
		for(node = my_table->table[table_index]; ; node = node->next)  {
			prev = node;

			if(strcmp(node->value, text) == 0)  {
				strcpy(node->value, text);
				collision = true;
				free(new_node->value);
				free(new_node);
				break;
			}

			if(node->next == NULL)
				break;
		}
		if(collision == false)  {
		        /* Otherwise we add the new hash value at the last */
			strcpy(new_node->value, text);
			node->next = new_node;
		}
	}
}

void delete_hash_table(symbol_table *my_table)  { /* Clean hash table*/
	for(int i=0; i<TABLE_LENGTH; i++)  {
		if(my_table->table[i])  {
			list_node* temp1 = my_table->table[i];
			list_node* temp2;
			while(temp1)  {
				temp2 = temp1->next;
				free(temp1->value);
				free(temp1);
				temp1 = temp2;
			}
			my_table->table[i] = NULL;
		}
	}
	free(my_table);
}

void print_hash_table(symbol_table *my_table)  {
	for(int i = 0; i < TABLE_LENGTH; i++)  {
		if(my_table->table[i])  {
			printf("id: %d \n", i);
			list_node *start=my_table->table[i];
			for(; start!=NULL; start = start->next)
				printf("\t %s\n", start->value);
		}
	}
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
