/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Seth Rothstein
 * [TERM] FALL 2023
 * 
 ****************************************/
#ifndef __ERROR_H__
#define __ERROR_H__

#include "parser.h"
#include <stdarg.h>

enum exitcode {
	// Error code 1 represents that given file does not exist.
	EXIT_INCORRECT_ARGUMENTS = 1,
	// Error code 2 represents that a file could not be opened.
	EXIT_CANNOT_OPEN_FILE = 2,
	// Error code 3 represents that there were too many instructions in the file.
	EXIT_TOO_MANY_INSTRUCTIONS = 3,
	// Error code 4 represents an invalid label (doesn't start with a letter).
	EXIT_INVALID_LABEL = 4,
	// Error code 5 represents that a label is already in the symbol table.
	EXIT_SYMBOL_ALREADY_EXISTS = 5,
};

void exit_program(enum exitcode code, ...);

#endif