
// Andrew West - sim_malicious.c - Abstraction of malicious behaviors

// ---------------------------- LOCAL INCLUDES -------------------------------

#include "sim_globals.h"

// --------------------------- GLOBAL VARIABLES ------------------------------

int* collective;		// Array holding user ID's of collective members
int mal_count = 0;	// The number of members in above array

// --------------------------- EXTERNAL FUNCTIONS-----------------------------

void malicious_compute_trust(Network* nw, int recv, int cycle){
	
	if(cycle == 0) // We have to get ALG init'ed before update called
		trans_alg_compute(nw, recv, cycle);

	if(STRATEGY == NAIVE)
		trans_alg_compute(nw, recv, cycle);
	
	else if(STRATEGY == ISOLATED){
		if(nw->ulib->users[recv].behavior != BEHAVE_GOOD){
			malicious_vector_set_fback(nw, HONEST, recv);
			trans_alg_compute(nw, recv, cycle);		
			malicious_vector_set_fback(nw, GLOBAL, recv);
		} else
			trans_alg_compute(nw, recv, cycle);
			
	} else if(STRATEGY == COLLECTIVE){
		int i; 
		if(cycle ==0){
			for(i=0; i < NUM_USERS; i++){
				if(nw->ulib->users[i].behavior != BEHAVE_GOOD)
					mal_count++;
			} // Count up number of non-'good' users on first pass
			collective = (int*) calloc(mal_count, sizeof(int));	
			int pos=0;
			for(i=0; i < NUM_USERS; i++){
				if(nw->ulib->users[i].behavior != BEHAVE_GOOD){
					collective[pos] = i;
					pos++;
				} // Then, on a second pass... 
			} // Add all non-"good" user ID's to a list
		} else{
			if(nw->ulib->users[recv].behavior != BEHAVE_GOOD){
				for(i=0; i < mal_count; i++)
					malicious_vector_set_fback(nw, HONEST, collective[i]);
				trans_alg_compute(nw, recv, cycle);
				for(i=0; i < mal_count; i++)
					malicious_vector_set_fback(nw, GLOBAL, collective[i]);
			} else
				trans_alg_compute(nw, recv, cycle);
		} // Setup strategy the first time, apply thereafter
	} // Change data set according to malicious strategy

}


// ----------------------------- LOCAL FUNCTIONS------------------------------

void malicious_vector_set_fback(Network* nw, feedback_t FT, int vec){
	int i;
	for(i=0; i < NUM_USERS; i++){
		switch_feedback_set(&nw->ulib->users[vec].vector[i], FT);
		trans_alg_update(nw, vec, i);
	} // Set all relations in some vector to a desired feedback setting
	return;
}

