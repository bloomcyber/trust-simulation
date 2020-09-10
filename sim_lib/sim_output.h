
// Andrew West - sim_output.h - Header file for sim_output.c

#ifndef SIM_OUTPUT_H
#define SIM_OUTPUT_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------


// ------------------------ FUNCTION PROTOTYPES -----------------------------

char* output_extension();
char* output_tsys();
char* output_strategy();

void print_statistics();
void reset_statistics();

#endif
