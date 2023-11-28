/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] Seth Rothstein
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "parser.h"

void add_predefined_symbols() {
	for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; ++i) {
		predefined_symbol symbol = predefined_symbols[i];
		symtable_insert(symbol.name, symbol.address);
	}
}

bool parse_A_instruction(const char *line, a_instruction *instr) {
	char *s = malloc(strlen(line));
	strcpy(s, line+1);
	char *s_end = NULL;
	long result = strtol(s, &s_end, 10);

	if (s == s_end) {
		instr->operand.label = malloc(strlen(line));
		strcpy(instr->operand.label, s);
		instr->is_addr = false;
	}
	else if (*s_end != 0) {
		return false;
	}
	else {
		instr->operand.address = result;
		instr->is_addr = true;
	}
	return true;
}


// Checks if a line is an A type instruction
bool is_Atype(const char *line) {
	if (line[0] == '@') {
		return true;
	}
	return false;
}

// Checks if a line is a label
bool is_label(const char *line) {
	if (line[0] == '(' && line[strlen(line) - 1] == ')') {
		return true;
	}
	return false;
}

// Checks if a line is a C type instruction
bool is_Ctype(const char *line) {
	if (is_Atype(line) || is_label(line)){
		return false;
	}
	return true;
}

// Extracts a label from a line
char *extract_label(const char *line, char* label) {
	int i = 0;
	for (const char *s = line; *s; s++) {
		if (*s != '(' && *s != ')') {
			label[i++] = *s;
		}
	}
	label[i] = '\0';
	return label;
}


/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s) {	

	char s_new[strlen(s) + 1];
	int i = 0;

	for (char *s2 = s; *s2; s2++) {
		if (*s2 == '/' && *(s2 + 1) == '/') {
			break;
		}
		else if (!isspace(*s2)) {
			s_new[i++] = *s2;
		}
	}
	
	s_new[i] = '\0';
	strcpy(s, s_new);

    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file) {
	
	char line[MAX_LINE_LENGTH] = {0};
	unsigned line_num = 0;
	unsigned inst_num = 0;
	instruction instr;

	add_predefined_symbols();

	while(fgets(line, sizeof(line), file)) {
		line_num++;
		
		if (inst_num > MAX_INSTRUCTIONS) {
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}

		strip(line);

		if (!*line) {
			continue;
		}
		char inst_type;
		if (is_Atype(line)) {
			inst_type = 'A';
			if (!parse_A_instruction(line, &instr.instr.a)) {
				exit_program(EXIT_INVALID_A_INSTR, line_num, line);
			}
			instr.type = Atype;
		}
		else if (is_label(line)) {
			inst_type = 'L';
		}
		else if (is_Ctype(line)) {
			inst_type = 'C';
		}
		if (inst_type == 'L') {
			char label[MAX_LABEL_LENGTH] = {0};
			strcpy(line, extract_label(line, label));
			if (isalpha(line[0]) == 0) {
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			}
			if (symtable_find(line) != NULL) {
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			}
			symtable_insert(line, inst_num);
			continue;
			// printf("%c  %s\n", inst_type, line);

		}

		// printf("%u: %c  %s\n", inst_num, inst_type, line);
		inst_num++;
	}
}

