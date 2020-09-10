
// Andrew West - sim_trans.c - Abstraction of simulator transaction funcs

// ---------------------------- LOCAL INCLUDES -------------------------------

#include "sim_globals.h"

// ------------------------- HIGH-LEVEL TRANS FUNC ---------------------------

void trans_perform(Network* nw, int cycle){
	trans_commit(nw, cycle);
	trans_queue(nw, cycle);
	return;
}

void trans_commit_remaining(Network* nw, int cycle){
	int i;
	for(i=0; i < BAND_PER; i++){
		trans_commit(nw, cycle+i);
	} // Commit all remaining transacs in delay queue
	return;
}

// ---------------------- QUEUE AND DEQUEUE TRANSACS -------------------------

void trans_commit(Network* nw, int cycle){
	Transaction* cur_t = &nw->dunit->t_queue[nw->dunit->pop_pointer];
	if(cur_t->commit_cycle == cycle){
		trans_file_handler(nw, cur_t->recv, cur_t->file_num, cur_t->valid);
		trans_fback_handler(nw->ulib, cur_t->send, cur_t->recv, cur_t->valid);
		nw->dunit->pop_pointer = (nw->dunit->pop_pointer + 1) % BAND_PER;
		trans_alg_update(nw, cur_t->recv, cur_t->send);
	} // One transaction commits per cycle (for now)
	return;
}

void trans_queue(Network* nw, int cycle){		
	int recv, send, file_num, i;
	parse_next_trans(); // Places data in Transaction trans_ex
	recv = trans_ex.recv;
	file_num = trans_ex.file_num;
	
	int cond1 = has_file(nw->flib, recv, file_num);
		// By hardcoding (cond2:=1), users have unlimited DL bandwidth
	int cond2 = bwidth_avail(nw->ulib->users[recv].bw_dl, cycle);
	if(cond1 || !cond2){
		NUM_RECV_BLK_TR++;
		return;
	} // If (receiving) user already has file, or no bandwidth, don't attempt

		// Compute trust over a feedback set which is determined by the malicious
		// user behavior being applied to the simulation.
	malicious_compute_trust(nw, recv, cycle);
	
		// Source selection is based on user behavior model
	user_t behavior = nw->ulib->users[recv].behavior;
	if(behavior == BEHAVE_GOOD)
		send = source_best_user(nw, recv, file_num, cycle);
	else if(behavior == BEHAVE_PURE)
		send = source_worst_user(nw, recv, file_num, cycle);
	else if(behavior == BEHAVE_PROV)
		send = source_worst_user(nw, recv, file_num, cycle);
	else if(behavior == BEHAVE_SYBL)
		send = source_worst_user(nw, recv, file_num, cycle);
	else if(behavior == BEHAVE_FEED)
		send = source_rand_user(nw, recv, file_num, cycle);
	else if(behavior == BEHAVE_DISG)
		send = source_rand_user(nw, recv, file_num, cycle);
	else // if(behavior == UNKNOWN)
		send = source_rand_user(nw, recv, file_num, cycle);

	if(send == -1){
		NUM_SEND_BLK_TR++;
		return; 
	} // If query unanswered, or no sources have b-width, abort transaction
	
		// Beyond this point, we assume transaction is proceeding
	int file_valid = valid_file(nw->flib, send, file_num);
	bwidth_use(nw->ulib->users[recv].bw_dl, cycle);
	bwidth_use(nw->ulib->users[send].bw_ul, cycle);
	
		// Code used for generating provider histograms. 
	/*if(cycle == 0)
		upload_count = (int*) calloc(NUM_USERS, sizeof(int));
	upload_count[send]++;
	if(cycle == (NUM_TRANS - 1)){
		printf("\n");
		for(i=0; i < NUM_USERS; i++)
			printf("%d,", upload_count[i]);
		printf("\n\n");
	} */ // Just print out upload counts in raw form

		// Now insert transaction into delay queue
	int pos = nw->dunit->push_pointer;
	nw->dunit->t_queue[pos].commit_cycle = (cycle + BAND_PER);
	nw->dunit->t_queue[pos].send = send;
	nw->dunit->t_queue[pos].recv = recv;
	nw->dunit->t_queue[pos].file_num = file_num;
	nw->dunit->t_queue[pos].valid = file_valid;
	nw->dunit->push_pointer = (nw->dunit->push_pointer + 1) % BAND_PER;
	return;
}

// ------------------------ COMMIT TRANSAC HELPERS ---------------------------

void trans_file_handler(Network* nw, int recv, int file_num, int valid){
	if(!valid){
		NUM_INVAL_TRANS++;
		if(nw->ulib->users[recv].behavior == BEHAVE_GOOD)
			NUM_GOOD_FAIL++;
		if(RAND_FP() > nw->ulib->users[recv].pct_cleanup)
			add_file(nw, recv, file_num, valid);
	} else{ // If a bad file is received
		if(nw->ulib->users[recv].behavior == BEHAVE_GOOD){
			NUM_GOOD_SUCC++;
			add_file(nw, recv, file_num, valid);
		} else if(RAND_FP() > (1.0 - nw->ulib->users[recv].pct_cleanup))
			add_file(nw, recv, file_num, valid);
	} // Else if a good file is received
	return;
}

void trans_fback_handler(User_Library* ulib, int send, int recv, int valid){

	int cond1 = ulib->users[send].behavior == BEHAVE_SYBL;
	int cond2 = ulib->users[recv].behavior == BEHAVE_SYBL;
	if(cond1 || cond2){
		NUM_FBACK_SYBL++;
		return;
	} // If sender or receiver is sybil, no feedback is recorded.
	
		// Sumbit both honest interaction history and (possibly dishonest) fback.
	Relation* rel = &ulib->users[recv].vector[send];
	if(valid)
		rel->honest_pos++;
	else
		rel->honest_neg++;
	
	if(RAND_FP() > ulib->users[recv].pct_honest){
		NUM_FBACK_LIES++;
		if(valid)
			rel->global_neg++;
		else
			rel->global_pos++;
	} else{ // Some users will be dishonest in providing feedback
		NUM_FBACK_TRUE++;
		if(valid)
			rel->global_pos++;
		else
			rel->global_neg++;
	} // Other users will be honest
	return;
}

// ---------------------- ALGORITHM SPECIFIC METHODS -------------------------

void trans_alg_update(Network* nw, int recv, int send){
	if(TSYS == EIGEN)
		eigen_update(nw, recv, send);
	else if(TSYS == BLOCK)
		block_update(nw, recv, send);
	else if(TSYS == ZHEYANG)
		zheyang_update(nw, recv, send);			
	else if(TSYS == ET_INC)
		etinc_update(nw, recv, send);
	else if(TSYS == TNA_SL)
		tnasl_update(nw, recv, send);
	else if(TSYS == SMART)
		smart_update(nw, recv, send);
	else if(TSYS == NONE)
		none_update(nw, recv, send);
}

void trans_alg_compute(Network* nw, int recv, int cycle){
	if(TSYS == EIGEN)
		eigen_compute_trust(nw, recv, cycle);
	else if(TSYS == BLOCK)
		block_compute_trust(nw, recv, cycle);
	else if(TSYS == SMART)
		smart_compute_trust(nw, recv, cycle);
	else if(TSYS == ZHEYANG)
		zheyang_compute_trust(nw, recv, cycle);
	else if(TSYS == ET_INC)
		etinc_compute_trust(nw, recv, cycle);
	else if(TSYS == TNA_SL)
		tnasl_compute_trust(nw, recv, cycle);
	else if(TSYS == NONE)
		none_compute_trust(nw, recv, cycle);
}

