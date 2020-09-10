
// Andrew West - tsys_etinc.h - Header file for tsys_etinc.c

#ifndef TSYS_ETINC_H
#define TSYS_ETINC_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------


// ------------------------ FUNCTION PROTOTYPES -----------------------------

void etinc_compute_trust(Network* nw, int user, int cycle);
void etinc_update(Network* nw, int new_vec, int new_row);

void etinc_take_snapshot(User_Library* ulib, int user);

#endif

