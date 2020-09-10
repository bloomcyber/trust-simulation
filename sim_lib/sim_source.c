
// Andrew West - sim_source.c - Abstraction of simulator source-select funcs

// ---------------------------- LOCAL INCLUDES -------------------------------

#include "sim_globals.h"

// ------------------------ SOURCE-SELECT FUNCTIONS --------------------------

int source_best_user(Network* nw, int recv, int file_num, int cycle){
	int return_val, i;
	float max_trust = (-1)*FLT_MAX;
	int pos_sources = 0;
	
	float* scratch_vec = (float*) calloc(NUM_USERS, sizeof(float));	
	if(scratch_vec == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allow trust vals to be persistent by manipulating in scratch vector
	
	int cond1, cond2;           
	for(i=0; i < NUM_USERS; i++){
		cond1 = has_file(nw->flib, i, file_num);
		cond2 = bwidth_avail(nw->ulib->users[i].bw_ul, cycle);
		if(!cond1 || !cond2)
			scratch_vec[i] = (-1)*FLT_MAX;
		else if(nw->ulib->users[recv].vector[i].trust_val > max_trust){
			pos_sources = 1;
			max_trust = nw->ulib->users[recv].vector[i].trust_val;
			scratch_vec[i] = max_trust;
		} else if(nw->ulib->users[recv].vector[i].trust_val == max_trust){
			pos_sources++;
			scratch_vec[i] = max_trust;
		} else
			scratch_vec[i] = (-1)*FLT_MAX;
	} // Count quantity of peers with maximum trust value
			
	if(pos_sources == 0)
		return (-1); // If no sources available, report that fact
		
	int source_num = ((int) (RAND_FP()*(pos_sources))) + 1;
	for(i=0; i < NUM_USERS; i++){
		if(scratch_vec[i] == max_trust)
			source_num--;
		if(source_num == 0){
			return_val = i;
			break;
		} // Break loop once we have arrived at randomly selected provider 
	} // Iterate over all peers
	free(scratch_vec);
	return return_val;
}

int source_worst_user(Network* nw, int recv, int file_num, int cycle){
	int return_val, i;
	float min_trust = FLT_MAX;
	int pos_sources = 0;
	
	float* scratch_vec = (float*) calloc(NUM_USERS, sizeof(float));	
	if(scratch_vec == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allow trust vals to be persistent by manipulating in scratch vector
	
	int cond1, cond2;
	for(i=0; i < NUM_USERS; i++){
		cond1 = has_file(nw->flib, i, file_num);
		cond2 = bwidth_avail(nw->ulib->users[i].bw_ul, cycle);
		if(!cond1 || !cond2)
			scratch_vec[i] = FLT_MAX;
		else if(nw->ulib->users[recv].vector[i].trust_val < min_trust){
			pos_sources = 1;
			min_trust = nw->ulib->users[recv].vector[i].trust_val;
			scratch_vec[i] = min_trust;
		} else if(nw->ulib->users[recv].vector[i].trust_val == min_trust){
			pos_sources++;
			scratch_vec[i] = min_trust;
		} else
			scratch_vec[i] = FLT_MAX;
	} // Count quantity of peers with lowest trust value
			
	if(pos_sources == 0)
		return (-1); // If no sources available, report that fact
		
	int source_num = ((int) (RAND_FP()*(pos_sources))) + 1;
	for(i=0; i < NUM_USERS; i++){
		if(scratch_vec[i] == min_trust)
			source_num--;
		if(source_num == 0){
			return_val = i;
			break;
		} // Break loop once we have arrived at randomly selected provider 
	} // Iterate over all peers
	free(scratch_vec);
	return return_val;
}

int source_rand_user(Network* nw, int recv, int file_num, int cycle){	
	int return_val, i;
	int pos_sources = 0;
	
	float* scratch_vec = (float*) calloc(NUM_USERS, sizeof(float));	
	if(scratch_vec == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allow trust vals to be persistent by manipulating in scratch vector
	
	int cond1, cond2;
	for(i=0; i < NUM_USERS; i++){
		cond1 = has_file(nw->flib, i, file_num);
		cond2 = bwidth_avail(nw->ulib->users[i].bw_ul, cycle);
		if(cond1 && cond2){
			pos_sources++;
			scratch_vec[i] = FLT_MAX;
		} else
			scratch_vec[i] = (-1)*FLT_MAX;
	} // Count quantity of potential sources
	
	if(pos_sources == 0)
		return (-1); // If no sources exist, this should be noted
	
	int source_num = ((int) (RAND_FP()*(pos_sources))) + 1;
	for(i=0; i < NUM_USERS; i++){
		if(scratch_vec[i] == FLT_MAX)
			source_num--;
		if(source_num == 0){
			return_val = i;
			break;
		} // Break loop once we have arrived at randomly selected provider 
	} // Iterate over all peers
	free(scratch_vec);
	return return_val;
}
	
