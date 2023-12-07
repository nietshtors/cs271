/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] Seth Rothstein
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "symtable.h"

Symbol* hashArray[SYMBOL_TABLE_SIZE]; 

// Hashes a string
int hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return (int)(hash % SYMBOL_TABLE_SIZE);
}

// Find
Symbol *symtable_find(char * key) {
	// Get hash
	int hashIndex = hash(key);

	// Move through array to an empty cell
	while(hashArray[hashIndex] != NULL) {
		if(strcmp(hashArray[hashIndex]->name, key) == 0) {
			return hashArray[hashIndex];
		}
		// Move to next cell
		++hashIndex;
		// Wrap to start
		hashIndex %= SYMBOL_TABLE_SIZE;
	}

	return NULL;
}


// Insert into symtable
void symtable_insert(char* key, hack_addr addr) {
	Symbol *item = (Symbol*) malloc(sizeof(Symbol) + 1);
	item->address = addr;
	strcpy(item->name, key);

	// Get hash
	int hashIndex = hash(key);

	// Move through array to an empty cell
	while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL) {
		// Move to next cell
		++hashIndex;
		// Wrap to start
		hashIndex %= SYMBOL_TABLE_SIZE;
	}

	hashArray[hashIndex] = item;
}

void symtable_display_table() {
	for(int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
		if(hashArray[i] != NULL) {
			printf(" (%s%d)", hashArray[i]->name, hashArray[i]->address);
		} 
		else {
			printf(" ~~ ");
		}
	}
	printf("\n");
}

void symtable_print_labels() {
   int i = 0;    
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
             printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->address);
        }
   }
} 