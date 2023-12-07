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

void parse_C_instruction(char *line, c_instruction *instr) {
	// DEST=COMP;JUMP
	char *token = NULL;
	char *jump = NULL;
	char *dest = NULL;
	char *comp = NULL;

	token = strtok(line, ";");
	jump = strtok(NULL, "");
	dest = strtok(token, "=");
	comp = strtok(NULL, "");

	if (comp == NULL) {
		comp = dest;
		dest = NULL;
	}

	int a;
	instr->jump = str_to_jumpid(jump);
	instr->dest = str_to_destid(dest);
	instr->comp = str_to_compid(comp, &a);
	instr->a = 1 ? a : 0;
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
int parse(FILE * file, instruction *instructions) {
	
	char line[MAX_LINE_LENGTH] = {0};
	unsigned line_num = 0;
	unsigned inst_num = 0;
	instruction instr;
	char tmp_line[MAX_LINE_LENGTH];

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

			if (instr.instr.a.is_addr == true) {
				printf("A: %d\n", instr.instr.a.operand.address);
			} else {
				printf("A: %s\n", instr.instr.a.operand.label);	
			}

			
		}
		else if (is_label(line)) {
			inst_type = 'L';
		}
		else if (is_Ctype(line)) {
			inst_type = 'C';
			strcpy(tmp_line, line);
			parse_C_instruction(tmp_line, &instr.instr.c);
			if (instr.instr.c.dest == DEST_INVALID) {
				exit_program(EXIT_INVALID_C_DEST, line_num, line);
			} else if (instr.instr.c.comp == COMP_INVALID) {
				exit_program(EXIT_INVALID_C_COMP, line_num, line);
			} else if (instr.instr.c.jump == JMP_INVALID) {
				exit_program(EXIT_INVALID_C_JUMP, line_num, line);
			}
			instr.type = Ctype;

			printf("C: d=%d, c=%d, j=%d\n", instr.instr.c.dest, instr.instr.c.comp, instr.instr.c.jump);
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

		// if (inst_type == "A") {

		// } else if (inst_type == "C") {
			
		// }

		// printf("%u: %c  %s\n", inst_num, inst_type, line);
		instructions[inst_num++] = instr;
	}
	return inst_num;
}

