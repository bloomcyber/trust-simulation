
// Andrew West - lib_bwidth.c - Abstraction of bandwidth unit behavior

// -------------------------- LOCAL INCLUDES --------------------------------

#include "globals.h"

// -------------------------- MEMORY ALLOCATION -----------------------------

BWidth_Unit* allocate_bwidth_unit(){
	BWidth_Unit* bwu = (BWidth_Unit*) malloc(sizeof(BWidth_Unit));
	bwu->usage_queue = (int*) calloc(BAND_MAX, sizeof(int));
	if(bwu == NULL || bwu->usage_queue == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allocate the network
	return bwu; 
}

// ------------------------- INITIALIZATION FUNC ----------------------------

void initialize_bwidth_unit(BWidth_Unit* bwu){
	int i;
	for(i=0; i < BAND_MAX;  i++)
		bwu->usage_queue[i] = INT_MIN;
	bwu->pointer = 0;
	return;
}

// ---------------------- B-WIDTH UNIT MAINTENANCE --------------------------

int bwidth_avail(BWidth_Unit* bwu, int cycle){
	if((cycle-BAND_PER) >= bwu->usage_queue[bwu->pointer])
		return 1;
	return 0;
}
	
	// PRECONDITION: Bandwidth must be available (per above method)
void bwidth_use(BWidth_Unit* bwu, int cycle){
	bwu->usage_queue[bwu->pointer] = cycle;
	bwu->pointer = (bwu->pointer+1) % BAND_MAX;
	return;
}

