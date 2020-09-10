
// Andrew West - gen_output.c - Abstraction of generator output funcs

// -------------------------- LOCAL INCLUDES --------------------------------

#include "gen_globals.h"

// --------------------------- OUTPUT FUNCTIONS ------------------------------

void print_header(){	
	fprintf(out, "%d Users\n", NUM_USERS);
	fprintf(out, "%d Files\n", NUM_FILES);
	fprintf(out, "%d Transactions\n", NUM_TRANS);
	fprintf(out, "%d Maximum Connections\n", BAND_MAX);
	fprintf(out, "%d Cycle Length per Upload-Download\n", BAND_PER);
	fprintf(out, "%d Warm-up Transactions\n", WARMUP);
	fprintf(out, "%f Zipf constant\n", ZIPF);
	fprintf(out, "%d Pre-Trusted Users\n", PRE_TRUSTED);
	fprintf(out, "%d Well-Behaved (Good) Users\n", USR_GOOD);
	fprintf(out, "%d Purely Malicious Users\n", USR_PURE);
	fprintf(out, "%d Feedback Skewing Users\n", USR_FEED);
	fprintf(out, "%d Malignant Providing Users\n", USR_PROV);
	fprintf(out, "%d Disguised Malicous Users\n", USR_DISG);
	fprintf(out, "%d Sybil Attack Users\n", USR_SYBL);
	fprintf(out, "%s Intelligent Trans. Generation\n", SMART_GEN);
	fprintf(out, "%ld Trace Generation Seed\n\n", RAND_SEED);
	printf("\nHeader complete...\n");
	return;
}

void print_users(Network* nw){
	int i;
	for(i=0; i < NUM_USERS; i++){
		fprintf(out, "(%f,", nw->ulib->users[i].pct_cleanup);
		fprintf(out, "%f,", nw->ulib->users[i].pct_honest);
		fprintf(out, "%d,", nw->ulib->users[i].behavior);
		fprintf(out, "%s)\n", print_bool(nw->ulib->users[i].pre_trusted));
	} // Print all User initialization data to trace
	fprintf(out, "\n"); // Blank separator
}

void print_file(int owner, int file_num, int valid){
	fprintf(out, "(%d,%d,%s)\n", owner, file_num, print_bool(valid));
}

void print_trans(int recv, int file_num){
	fprintf(out, "(%d,%d)\n", recv, file_num);
}

char* print_bool(int boolean){
	if(boolean)
		return "true";
	else
		return "false";
}

