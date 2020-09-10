
// Andrew West - sim_source.h - Header file for sim_source.c

#ifndef SIM_SOURCE_H
#define SIM_SOURCE_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------


// ------------------------ FUNCTION PROTOTYPES -----------------------------

int source_best_user(Network* nw, int recv, int file_num, int cycle);
int source_worst_user(Network* nw, int recv, int file_num, int cycle);
int source_rand_user(Network* nw, int recv, int file_num, int cycle);

#endif
