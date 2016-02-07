#include "hash_table.h"

int main(){

    char* names[] = {"Abhijeet", "Ramdev", "Kamdev", "Shatmatdev", "This is it",
    "You are shit", "This is what I want to become", "I am a token",
    "Hallelujah", "I am the king of the world", "How I met you mother?",
    "Kamdev", "Luftwaffe"};

    for(int i = 0; i < (sizeof(names))/sizeof(names[0]); ++i){
        insert_hash(names[i]);
    }
    delete_hash_table();
    print_hash_table(); // Now the motive is to protect Ramdev.
}
