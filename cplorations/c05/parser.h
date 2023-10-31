/****************************************
 * C-ploration 5 for CS 271
 * 
 * [NAME] Seth Rothstein
 * [TERM] FALL 2023
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH  200

/** function prototypes **/
bool is_Atype(const char *);

bool is_label(const char *);

bool is_Ctype(const char *);

char *strip(char *s);

void parse(FILE * file);
