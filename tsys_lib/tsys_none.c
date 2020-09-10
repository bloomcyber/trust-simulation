
// Andrew West - tsys_none.c - Abstraction of an absence of trust management

// ---------------------------- LOCAL INCLUDES -------------------------------

#include "sim_globals.h"

// ---------------------------- TRUST FUNCTIONS -----------------------------

void none_compute_trust(Network* nw, int user, int cycle){
	if(cycle == 0){
		int i, j;
		for(i=0; i < NUM_USERS; i++){
			for(j=0; j < NUM_USERS; j++){
				nw->ulib->users[i].vector[j].trust_val = 1.0;
			} // Set all relations to same trust value
		} // Do so for all users in the network
	} // Because trust values are persistent, this only needs done once
	return;
}

void none_update(Network* nw, int new_vec, int new_row){
		// Do nothing, let trust values persist
	return;
}

