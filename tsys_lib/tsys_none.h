                                        
// Andrew West - tsys_none.h - Header file for tsys_none.c

#ifndef TSYS_NONE_H
#define TSYS_NONE_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------


// ------------------------ FUNCTION PROTOTYPES -----------------------------

void none_compute_trust(Network* nw, int user, int cycle);
void none_update(Network* nw, int new_vec, int new_row);

#endif

