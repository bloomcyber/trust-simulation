
// Andrew West - sim_output.c - Abstraction of simulator output funcs

// ---------------------------- LOCAL INCLUDES -------------------------------

#include "sim_globals.h"

// ---------------------------- STRING FUNCTIONS -----------------------------

char* output_extension(){
	char* extension;
	if(TSYS == EIGEN)
		extension = "eigen";
	else if(TSYS == ET_INC)
		extension = "etinc";
	else if(TSYS == BLOCK)
		extension = "block";
	else if(TSYS == ZHEYANG)
		extension = "zheyang";
	else if(TSYS == TNA_SL)
		extension = "tnasl";
	else if(TSYS == SMART)
		extension = "smart";
	else if(TSYS == NONE)
		extension = "none";
	return extension;
}

char* output_tsys(){
	char* tsys_str;
	if(TSYS == EIGEN)
		tsys_str = "EigenTrust";
	else if(TSYS == ET_INC)
		tsys_str = "EigenTrust-Incremental";
	else if(TSYS == BLOCK)
		tsys_str = "Block";
	else if(TSYS == SMART)
		tsys_str = "Smart";
	else if(TSYS == ZHEYANG)
		tsys_str = "Zheyang";
	else if(TSYS == TNA_SL)
		tsys_str = "TNA-SL";
	else if(TSYS == NONE)
		tsys_str = "None";
	return tsys_str;
}

char* output_strategy(){
	char* strategy_str;
	if(STRATEGY == NAIVE)
		strategy_str = "Naive";
	else if(STRATEGY == ISOLATED)
		strategy_str = "Isolated";
	else if(STRATEGY == COLLECTIVE)
		strategy_str = "Collective";
	return strategy_str;
}

// ---------------------------- PRINT FUNCTIONS ------------------------------

//
// Note that the header output is taken care of in sim_parse.c 
//

void print_statistics(){
	
	int INCMPLETE_TRANS = (NUM_RECV_BLK_TR + NUM_SEND_BLK_TR);
	int COMPLETED_TRANS = (NUM_TRANS - INCMPLETE_TRANS);
	int NUM_VALID_TRANS = (COMPLETED_TRANS - NUM_INVAL_TRANS);
	int TOTAL_GOOD_TRANS = (NUM_GOOD_SUCC + NUM_GOOD_FAIL);
	
	fprintf(out, "-------- TRANSACTION OVERVIEW --------\n");
	fprintf(out, ">Transacts Attempted:    %d\n", NUM_TRANS);
	fprintf(out, ">Transacts Completed:    %d\n", COMPLETED_TRANS);
	fprintf(out, ">Transacts Incomplete:   %d\n\n", INCMPLETE_TRANS);

	fprintf(out, "-------- INCOMPLETE TRANS SUM --------\n");
	fprintf(out, ">Transacts Incomplete:   %d\n", INCMPLETE_TRANS);
	fprintf(out, ">Reception Declined:     %d\n", NUM_RECV_BLK_TR);
	fprintf(out, ">No Eligible Senders:    %d\n\n", NUM_SEND_BLK_TR);
	
	fprintf(out, "--------- COMPLETE TRANS SUM ---------\n");
	fprintf(out, ">Transacts Completed:    %d\n", COMPLETED_TRANS);
	fprintf(out, ">Valid Transactions:     %d\n", NUM_VALID_TRANS);
	fprintf(out, ">Invalid Transactions:   %d\n\n", NUM_INVAL_TRANS);
	
	fprintf(out, "--------- FEEDBACK OVERVIEW ----------\n");
	fprintf(out, ">Feedbacks Committed:    %d\n", COMPLETED_TRANS);
	fprintf(out, ">Truthful Feedbacks:     %d\n", NUM_FBACK_TRUE);
	fprintf(out, ">Dishonest Feedbacks:    %d\n", NUM_FBACK_LIES);
	fprintf(out, ">Sybil-User Feedbacks:   %d\n\n", NUM_FBACK_SYBL);
	
	fprintf(out, "--------- EVALUATION METRIC ----------\n");
	fprintf(out, ">Good User Transacts:    %d\n", TOTAL_GOOD_TRANS);
	fprintf(out, ">Good User Successes:    %d\n", NUM_GOOD_SUCC);
	fprintf(out, ">Good User Failures:     %d\n", NUM_GOOD_FAIL);

	return;
}

// ---------------------------- STAT FUNCTIONS ------------------------------

void reset_statistics(){
	NUM_INVAL_TRANS = 0;
	NUM_RECV_BLK_TR = 0;
	NUM_SEND_BLK_TR = 0;
	NUM_FBACK_TRUE = 0;
	NUM_FBACK_LIES = 0;
	NUM_FBACK_SYBL = 0;
	NUM_GOOD_SUCC = 0;
	NUM_GOOD_FAIL = 0; 
	return;
}

