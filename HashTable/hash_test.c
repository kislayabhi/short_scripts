#include "hash_table.h"
#include <stdio.h>

int main(){

    char* names[] = {"Abhijeet", "Ramdev", "Kamdev", "Shatmatdev", "This is it",
    "You are shit", "This is what I want to become", "I am a token",
    "Hallelujah", "I am the king of the world", "How I met you mother?",
    "Kamdev", "Luftwaffe"};

    printf("\t%lu\n",sizeof(names));
    for(int i = 0; i < (sizeof(names))/sizeof(names[0]); ++i){
        insert_hash(names[i]);
    }
    print_hash_table();
    delete_hash_table();
    print_hash_table(); 
}
