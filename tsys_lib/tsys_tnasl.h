                                        
// Andrew West - tsys_subj.h - Header file for tsys_tnasl.c

#ifndef TSYS_TNASL_H
#define TSYS_TNASL_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------

typedef struct{
	float b; // Belief
	float d; // Disbelief
	float u; // Uncertainty
	float a; // Base-rate
} Opinion;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

void tnasl_compute_trust(Network* nw, int user, int cycle);
void tnasl_update(Network* nw, int vec, int row);

void tnasl_initialize(User_Library* ulib);
void tnasl_master(User_Library* ulib, int user);
int tnasl_multiply(Opinion* vec, Opinion** matrix, Opinion* dest);

void op_discount(Opinion* op1, Opinion* op2, Opinion* dest);
void op_consensus(Opinion* op1, Opinion* op2, Opinion* dest);
float op_ev(Opinion* op);
void op_assign(Opinion* op1, Opinion* op2);
int op_compare(Opinion* this, Opinion* that);

#endif

