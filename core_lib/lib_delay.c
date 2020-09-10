
// Andrew West - lib_delay.c - Abstraction of delay unit behavior

// -------------------------- LOCAL INCLUDES --------------------------------

#include "globals.h"

// -------------------------- MEMORY ALLOCATION -----------------------------

Delay_Unit* allocate_delay_unit(){
	Delay_Unit* dunit = (Delay_Unit*) malloc(sizeof(Delay_Unit));
	dunit->t_queue = (Transaction*) calloc(BAND_PER, sizeof(Transaction));
	if(dunit == NULL || dunit->t_queue == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allocate Delay_Unit pointer and Transaction array
	return dunit;
}

// ------------------------ INITIALIZATION FUNCS ----------------------------

void initialize_delay_unit(Delay_Unit* dunit){
	dunit->push_pointer = 0;
	dunit->pop_pointer = 0;
	int i;
	for(i=0; i < BAND_PER; i++){
		dunit->t_queue[i].commit_cycle = -1;
		dunit->t_queue[i].send = -1;
		dunit->t_queue[i].recv = -1;
		dunit->t_queue[i].file_num = -1;
		dunit->t_queue[i].valid = -1;
	} // Init each queued transaction as invalid to prevent commital
}

