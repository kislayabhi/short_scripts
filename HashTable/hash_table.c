#include "stdio.h"
#include "hash_table.h"

symbol_table my_table;

/* ----------Function Definition---------- */


bool insert_hash(char* str) // insert the string at the generated hash.
{
    unsigned int hash_value = generate_RSHash(str, strlen(str));
    // We keep the array size of 100.
    unsigned int table_index = hash_value%100;

    if(!my_table.table[table_index]){ // Initial case
        list_node* new_node = (list_node*)malloc(sizeof(list_node));
        my_table.table[table_index] = new_node;
        new_node->value = str;
        new_node->next = NULL;
    }
    else{
        list_node* node = my_table.table[table_index];
        bool collision = false;
        while(1){// If we have same value somewhere in the ll, we overwrite.
            if(strcmp(node->value, str) == 0){
                node->value = str;
                collision = true;
                break;
            }
            if(node->next==NULL) break;
            node = node->next;
        }
        if(collision==false){
            /* Otherwise we add the new hash value at the last */
            list_node* new_node = (list_node*)malloc(sizeof(list_node));
            new_node->value = str;
            new_node->next = NULL;
            node->next = new_node;
        }
    }
}

void delete_hash_table(){
    for(int i=0; i<100; i++)
        if(my_table.table[i]){
            list_node* temp1 = my_table.table[i];
            list_node* temp2;
            while(temp1){
                temp2 = temp1->next;
                free(temp1);
                temp1 = temp2;
            }
            my_table.table[i] = NULL;
        }
}

void print_hash_table()
{
    for(int i=0; i<100; i++)
        if(my_table.table[i]){
            printf("key: %d \n", i);
            print_till_end(my_table.table[i]);
        }
}

void print_till_end(list_node* start){
    while(start){
        printf("\t %s\n", start->value);
        start = start->next;
    }
}

unsigned int generate_RSHash(char* str, unsigned int len)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++){
      hash = hash * a + (*str);
      a = a * b;
   }
   return hash;
}
/* End Of RS Hash Function */
