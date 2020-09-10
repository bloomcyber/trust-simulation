                                        
// Andrew West - tsys_subj.h - Header file for tsys_tnasl.c

#ifndef TSYS_ZHEYANG_H
#define TSYS_ZHEYANG_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------

typedef struct{
	float b; // Belief
	float d; // Disbelief
	float u; // Uncertainty
	float a; // Base-rate
} Opinionz;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

void zheyang_compute_trust(Network* nw, int user, int cycle);
void zheyang_update(Network* nw, int vec, int row);

void zheyang_initialize(User_Library* ulib);
void zheyang_master(User_Library* ulib, int user);
int zheyang_multiply(Opinionz* vec, Opinionz** matrix, Opinionz* dest);

//void op_discount(Opinion* op1, Opinion* op2, Opinion* dest);
//void op_consensus(Opinion* op1, Opinion* op2, Opinion* dest);
float zop_ev(Opinionz* op);
void zop_assign(Opinionz* op1, Opinionz* op2);
int zop_compare(Opinionz* this, Opinionz* that);

#endif

