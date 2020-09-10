
// Andrew West - lib_relation.c - Abstraction of relation behavior

// -------------------------- LOCAL INCLUDES --------------------------------

#include "globals.h"

// -------------------------- MEMORY ALLOCATION -----------------------------

Relation* allocate_rel_vector(){
	Relation* vec = (Relation*) calloc(NUM_USERS, sizeof(Relation));
	if(vec == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allocate the network
	return vec;
}

// ------------------------- INITIALIZATION FUNC ----------------------------

void initialize_rel(Relation* rel){	
	rel->global_pos = 0;
	rel->global_neg = 0;
	rel->honest_pos = 0;
	rel->honest_neg = 0;
	rel->trust_val = 0.0;
	rel->pos = &rel->global_pos;
	rel->neg = &rel->global_neg;
	return;	
}

// ----------------------------- OTHER FUNCS --------------------------------

void switch_feedback_set(Relation* rel, feedback_t FT){	
	if(FT == GLOBAL){
		rel->pos = &rel->global_pos;
		rel->neg = &rel->global_neg;
	} else{ // if(FT == HONEST)
		rel->pos = &rel->honest_pos;
		rel->neg = &rel->honest_neg;
	} // Switch feedback access point per parameter
}

