
// Andrew West - sim_parse.h - Header file for sim_parse.c

#ifndef SIM_PARSE_H
#define SIM_PARSE_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------


// ------------------------ FUNCTION PROTOTYPES -----------------------------

void parse_and_print_globals();
void parse_users(User_Library* ulib);
void parse_file_libs(Network* nw);
void parse_next_trans();

int parse_bool(char* string);
char* atow(char* string);

#endif
