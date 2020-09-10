
// Andrew West - tsys_etinc.c - Abstraction of EigenTrust-Incremental system

// ---------------------------- LOCAL INCLUDES -------------------------------

#include "sim_globals.h"

// -------------------------- GLOBAL VARIABLES -------------------------------

int cur_skip = 1;
float* snapshot;

// ------------------------- HIGH-LEVEL TRUST CALLS -------------------------

void etinc_compute_trust(Network* nw, int user, int cycle){
	int bool, i, j;
	if(cycle == 0){
		eigen_initialize(nw->ulib);
		snapshot = (float*) calloc(NUM_USERS, sizeof(float));
		if(snapshot == NULL){
			printf("\nMemory allocation failed. Aborting.\n\n");
			exit(1);
		} // Allocate memory for the snapshot vector
		eigen_trust_multiply(nw->ulib, user, 8);
		etinc_take_snapshot(nw->ulib, user);
	} // Setup infrastructure on first call
	
	else if(cycle % cur_skip == 0){ 
		bool = eigen_converged(snapshot, eigen_trust_multiply(nw->ulib, user, 8));
		if((bool) && (cur_skip != 64))
			cur_skip *= 2;
		else if((!bool) && (cur_skip != 1))
			cur_skip /= 2;
		
		etinc_take_snapshot(nw->ulib, user);
		for(i=0; i < NUM_USERS; i++){
			for(j=0; j < NUM_USERS; j++)
				nw->ulib->users[j].vector[i].trust_val = snapshot[i];
		} // Set trust globally, not just one vector as in 'eigen'
		
	} // Only recalculate ever 'cur_skip' cycles
	return;
}

void etinc_update(Network* nw, int new_vec, int new_row){
	eigen_normalize_vector(nw->ulib, new_vec);
	return;
}


// ----------------------------- TRUST HELPERS ------------------------------

void etinc_take_snapshot(User_Library* ulib, int user){
	int i;
	for(i=0; i < NUM_USERS; i++){
		snapshot[i] = ulib->users[user].vector[i].trust_val;
	} // Save a particular users trust vector
	return;
}


