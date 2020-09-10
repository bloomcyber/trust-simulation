
// Andrew West - sim_trans.h - Header file for sim_trans.c

#ifndef SIM_TRANS_H
#define SIM_TRANS_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------

// int* upload_count;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

void trans_perform(Network* nw, int cycle);
void trans_commit_remaining(Network* nw, int cycle);
void trans_commit(Network* nw, int cycle);
void trans_queue(Network* nw, int cycle);
void trans_file_handler(Network* nw, int recv, int file_num, int valid);
void trans_fback_handler(User_Library* ulib, int send, int recv, int valid);

void trans_alg_update(Network* nw, int recv, int send);
void trans_alg_compute(Network* nw, int recv, int cycle);

#endif
