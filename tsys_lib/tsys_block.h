                                        
// Andrew West - tsys_subj.h - Header file for tsys_tnasl.c

#ifndef TSYS_BLOCK_H
#define TSYS_BLOCK_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------

typedef struct{
	float b; // Belief
	float d; // Disbelief
	float u; // Uncertainty
	float a; // Base-rate
} Opinionb;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

void block_compute_trust(Network* nw, int user, int cycle);
void block_update(Network* nw, int vec, int row);

void block_initialize(User_Library* ulib);
void block_master(User_Library* ulib, int user);
int block_multiply(Opinionb* vec, Opinionb** matrix, Opinionb* dest);

//void op_discount(Opinion* op1, Opinion* op2, Opinion* dest);
//void op_consensus(Opinion* op1, Opinion* op2, Opinion* dest);
float bop_ev(Opinionb* op);
void bop_assign(Opinionb* op1, Opinionb* op2);
int bop_compare(Opinionb* this, Opinionb* that);

#endif

