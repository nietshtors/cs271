/****************************************
 * Project 6 for CS 271
 * 
 * [NAME] Seth Rothstein
 * [TERM] FALL 2023
 * 
 ****************************************/
#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define SYMBOL_TABLE_SIZE 1000

typedef int16_t hack_addr;

typedef struct Symbol {
	char name[MAX_LABEL_LENGTH];
	hack_addr address;
} Symbol;

int hash(char *str);
Symbol *symtable_find(char * key);
void symtable_insert(char* key, hack_addr addr);
void symtable_display_table();
void symtable_print_labels();

#endif