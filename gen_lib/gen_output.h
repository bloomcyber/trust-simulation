
// Andrew West - gen_output.h - Header file for gen_output.c

#ifndef GEN_OUTPUT_H
#define GEN_OUTPUT_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------


// ------------------------ FUNCTION PROTOTYPES -----------------------------

void print_header();
void print_users(Network* nw);
void print_trans(int recv, int file_num);
void print_file(int owner, int file_num, int valid);
char* print_bool(int boolean);

#endif

