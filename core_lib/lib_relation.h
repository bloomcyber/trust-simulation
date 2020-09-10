
// Andrew West - lib_relation.h - Header file for lib_relation.c

#ifndef RELATION_LIB_H
#define RELATION_LIB_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------

typedef enum{
	GLOBAL,
	HONEST
} feedback_t;

typedef struct{
	int* pos;	// Should be for access calls 
	int* neg;
	int global_pos; // Should be used for update calls
	int global_neg;
	int honest_pos;
	int honest_neg;
	float trust_val;
} Relation;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

Relation* allocate_rel_vector();
void initialize_rel(Relation* rel);

void switch_feedback_set(Relation* rel, feedback_t FT);

#endif
