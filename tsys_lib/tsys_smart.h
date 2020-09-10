                                        
// Andrew West - tsys_subj.h - Header file for tsys_tnasl.c

#ifndef TSYS_SMART_H
#define TSYS_SMART_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------

typedef struct{
	float b; // Belief
	float d; // Disbelief
	float u; // Uncertainty
	float at; // attack - by venkat
	float h; // history - by venkat
	float t; // trust score - by venkat
	float a; // Base-rate
} Opinionsmart;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

void smart_compute_trust(Network* nw, int user, int cycle);
void smart_update(Network* nw, int vec, int row);

void smart_initialize(User_Library* ulib);
void smart_master(User_Library* ulib, int user);
int smart_multiply(Opinionsmart* vec, Opinionsmart** matrix, Opinionsmart* dest);

void sop_discount(Opinionsmart* op1, Opinionsmart* op2, Opinionsmart* dest);
void sop_consensus(Opinionsmart* op1, Opinionsmart* op2, Opinionsmart* dest);
float sop_ev(Opinionsmart* op);
void sop_assign(Opinionsmart* op1, Opinionsmart* op2);
int sop_compare(Opinionsmart* this, Opinionsmart* that);

#endif

