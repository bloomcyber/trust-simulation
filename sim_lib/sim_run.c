
// Andrew West - sim_run.c - Given an input trace file, and trust management
// algorithm, simulate the trace in that environment, outputting performance
// statistics. This version implements bandwidth restriction. 
//
// See the enclosed README document for usage information.
//
// -------------------------- LOCAL INCLUDES --------------------------------

#include "sim_globals.h"

// -------------------------- GLOBAL VARIABLES ------------------------------

int NUM_USERS;           // # of peers in the network
int NUM_FILES;           // # of distinct files in network
int NUM_TRANS;           // # of transactions to simulate
int BAND_MAX;            // # of max upload/download connections per user
int BAND_PER;            // # of time units each upload/download requires
int WARMUP;              // # of warmup insns before statistical tabulation
int PRE_TRUSTED;         // # of pre-trusted peers, a subset of 'good' users
long RAND_SEED;          // Seed initializing event randomness

trust_alg_t TSYS;        // Trust system employed by this simulation run
mal_t STRATEGY; 				 // Malicious strategy being employed
               
FILE* in;                // Filestream to output file (write permission)
FILE* out;               // Filestream to input file (read permissions)
char* FILE_NAME;         // Filename of file about to be opened/closed
char cur_line[100];      // Buffer where in-read lines are stored
char scratch_str[100];   // Extra buffer to help in string manipulation
Transaction trans_ex;    // Transaction buffer for passing around data

int COMPUTE_UP_TO;

int NUM_INVAL_TRANS = 0; // # of invalid transactions completed
int NUM_RECV_BLK_TR = 0; // # of transactions prevented at receiver-level
int NUM_SEND_BLK_TR = 0; // # of transactions lost due to lack of source
int NUM_FBACK_TRUE = 0;  // # of honest feedbacks comitted
int NUM_FBACK_LIES = 0;  // # of dis-honest feedbacks comitted
int NUM_FBACK_SYBL = 0;  // # of sybil feedbacks "committed"
int NUM_GOOD_SUCC = 0;   // # of valid trans initiated by good users
int NUM_GOOD_FAIL = 0;   // # of invalid trans initiated by good users

// ------------------------ FUNCTION PROTOTYPES -----------------------------

int parse_arguments(int argc, char *argv[]);

// ---------------------------- MAIN ROUTINE --------------------------------

int main(int argc, char* argv[]){
	
	if(!parse_arguments(argc, argv))
		return 1; // Parse arguments
	
		// The output file replaces extension ".trace" with tsys extension
	strncpy(scratch_str, FILE_NAME, (size_t) strlen(FILE_NAME)-strlen("trace"));
	strncat(scratch_str, (char*) output_extension(), 5);
	memcpy(FILE_NAME, scratch_str, 100);
	out = fopen(FILE_NAME, "w");
	RAND_SEED = time(NULL);
	srand(RAND_SEED);
	
		// Read in params. Then allocate/init network
	parse_and_print_globals();
	Network* nw = allocate_network();
	initialize_network(nw);
	
		// Read in user/file data from trace
	parse_users(nw->ulib);	
	parse_file_libs(nw);
	printf("\nTrace file parsed and static initialization complete...\n");
	
		// Peform the warm-up transactions
	printf("Beginning warm-up phase... (%d transactions)\n", WARMUP);
	int cycle;
	for(cycle=0; cycle < WARMUP; cycle++){
		trans_perform(nw, cycle);
		if((cycle % 500 == 0) && (cycle != 0)){
			printf("Warm-up transactions completed: %d...\n", cycle);
			fflush(stdout);
		} // Periodic status updates during warm-up phase		
	} // Parse and dynamically perform transactions
	printf("Warm-up phase complete...\n");
	
		// Reset stats and perform actual transactions
	reset_statistics();
	printf("Beginning simulation phase... (%d transactions)\n", NUM_TRANS);
	for(cycle; cycle < (WARMUP + NUM_TRANS); cycle++){
		trans_perform(nw, cycle);
		if(((cycle-WARMUP) % 500 == 0) && (cycle != 0)){
			printf("Transactions completed so far: %d...\n", (cycle-WARMUP));
			fflush(stdout);
		} // Periodic status updates during simulation phase
	} // Parse and dynamically perform transactions
	printf("Simulation phase complete...\n");
	trans_commit_remaining(nw, cycle); // Commit all queued
	
		// Output final results
	print_statistics(nw);
	printf("Run complete! Data written to %s\n", FILE_NAME);
	printf("Simulation runtime: %f secs\n\n", (clock()/(CLOCKS_PER_SEC*1.0)));
	
		// Cleanup and exit
	fclose(out);
	fclose(in);
	
	return 0;
}

// --------------------------- PARSING FUNCTION -----------------------------

int parse_arguments(int argc, char *argv[]){
	if(argc != 7){
		printf("\nInvalid # of arguments. Aborting.\n\n");
		return 0;
	} // Check the number of arguments
	
	int i;
	for(i=2; i <= argc; i+=2){
		if(!strcmp("-input", argv[i-1]))
			FILE_NAME = argv[i];
		else if(!strcmp("-tm", argv[i-1])){
			if(!strcmp("eigen", argv[i]) || !strcmp("eigentrust", argv[i]))
				TSYS = EIGEN;
			else if(!strcmp("etinc", argv[i]) || !strcmp("et_inc", argv[i]))
				TSYS = ET_INC;
			else if(!strcmp("block", argv[i]) || !strcmp("block", argv[i]))
				TSYS = BLOCK;
			else if(!strcmp("smart", argv[i]) || !strcmp("smart", argv[i]))
				TSYS = SMART;
			else if(!strcmp("zheyang", argv[i]) || !strcmp("zheyang", argv[i]))
				TSYS = ZHEYANG;
			else if(!strcmp("tnasl", argv[i]) || !strcmp("tna_sl", argv[i]))
				TSYS = TNA_SL;
			else if(!strcmp("none", argv[i]))
				TSYS = NONE;
			else
				TSYS = NONE;
		} else if(!strcmp("-strategy", argv[i-1])){
			if(!strcmp("isolated", argv[i]))
				STRATEGY = ISOLATED;
			else if(!strcmp("collective", argv[i]))
				STRATEGY = COLLECTIVE;
			else
				STRATEGY = NAIVE;			
		} else{ // Assign the trust algorithm to be used
			printf("\nRequired argument missing. Aborting.\n\n");
			return 0;
		}  // Neither '-input' or '-tm' or '-strategy' should be omitted
	} // Parse arguments. Check for required flags.
	
	in = fopen(FILE_NAME, "r");
	if(in == NULL){
		printf("\nError opening trace file. Aborting.\n\n");
		return 0;
	} // Open the input file, report error if necessary
	return 1;
}

