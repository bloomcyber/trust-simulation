
// Andrew West - gen_trace.c - A program that generates trace files
// that can be used in the evaluation of trust management systems.
//
// See the enclosed README document for usage information
//
// -------------------------- LOCAL INCLUDES --------------------------------

#include "gen_globals.h"

// ------------------------ FUNCTION PROTOTYPES -----------------------------

int parse_arguments(int argc, char* argv[]);

// ----------------------- GLOBAL VAR DEFAULTS ------------------------------

int NUM_USERS = 100;
int NUM_FILES = 5000;
int NUM_TRANS = 10000;
float ZIPF = 0.4;
char* OUTPUT  = "trace_0.trace";

int PRE_TRUSTED = 5;
int USR_GOOD = 100;
int USR_PURE = 0;
int USR_FEED = 0;
int USR_PROV = 0;
int USR_DISG = 0;
int USR_SYBL = 0;

int BAND_MAX = 2;
int BAND_PER = 1;

int WARMUP = 0;
char* SMART_GEN = "true";
FILE* out;

int AV_FILES = 0;
long RAND_SEED = (long) NULL;

// ---------------------------- MAIN ROUTINE --------------------------------

int main(int argc, char *argv[]){

	if(!parse_arguments(argc, argv))
		return 1; // Parse arguments

		// Open and print header on trace file
	RAND_SEED = time(NULL);
	srand(RAND_SEED);
	out = fopen(OUTPUT, "w");
	print_header();

	Network* nw = allocate_network();
	initialize_network(nw);

  generate_user_lib(nw->ulib);
	print_users(nw);
	printf("User initialization complete...\n");
	generate_file_lib(nw);
	printf("Library initialization complete...\n");

	int i;
	for(i=0; i < (NUM_TRANS + WARMUP); i++){
		if(!strcmp(SMART_GEN, "true"))
			generate_transaction_smart(nw);
		else
			generate_transaction_naive(nw);
	} // Schedule the specified number of transactions per parameterization
	printf("Transaction generation complete...\n");
	printf("Done! Output written to %s\n\n", OUTPUT);

	fclose(out);
	return(0);
}

// --------------------------- PARSING FUNCTION ------------------------------

int parse_arguments(int argc, char* argv[]){
	if(argc % 2 == 0){
		printf("\nInvalid # of arguments. Aborting.\n\n");
		return 0;
	} // Check the number of arguments

	int i;
	for(i=2; i <= argc; i+=2){
		if(!strcmp("-users", argv[i-1]))
			NUM_USERS = atoi(argv[i]);
		else if(!strcmp("-files", argv[i-1]))
			NUM_FILES = atoi(argv[i]);
		else if(!strcmp("-trans", argv[i-1]))
			NUM_TRANS = atoi(argv[i]);
		else if(!strcmp("-zipf", argv[i-1]))
			ZIPF = atof(argv[i]);
		else if(!strcmp("-output", argv[i-1]))
			OUTPUT = argv[i];
		else if(!strcmp("-usr:pre_trusted", argv[i-1]))
			PRE_TRUSTED = atoi(argv[i]);
		else if(!strcmp("-usr:purely", argv[i-1]))
			USR_PURE = atoi(argv[i]);
		else if(!strcmp("-usr:feedback", argv[i-1]))
			USR_FEED = atoi(argv[i]);
		else if(!strcmp("-usr:provider", argv[i-1]))
			USR_PROV = atoi(argv[i]);
		else if(!strcmp("-usr:disguise", argv[i-1]))
			USR_DISG = atoi(argv[i]);
		else if(!strcmp("-usr:sybil", argv[i-1]))
			USR_SYBL = atoi(argv[i]);
		else if(!strcmp("-band:max_conn", argv[i-1]))
			BAND_MAX = atoi(argv[i]);
		else if(!strcmp("-band:period", argv[i-1]))
			BAND_PER = atoi(argv[i]);
		else if(!strcmp("-mode:smartgen", argv[i-1]))
			SMART_GEN = argv[i];
		else if(!strcmp("-mode:warmup", argv[i-1]))
			WARMUP = atoi(argv[i]);
		else{
			printf("\nInvalid argument structure. Aborting.\n\n");
			return 0;
		} // Catch unsupported arguments
	} // Parse arguments

	USR_GOOD = (NUM_USERS-USR_PURE-USR_FEED-USR_PROV-USR_DISG-USR_SYBL);
	if(USR_GOOD < 0){
		printf("\nError: Number of malicious users > total users. Aborting.\n\n");
		return 0;
	} // Make sure user counts are legal

	if(PRE_TRUSTED > USR_GOOD){
		printf("\nError: Number of pre-trusted users > good users. Aborting.\n\n");
		return 0;
	} // Make sure pre-trusted count is legal

	char* extension = (char*) calloc(6, sizeof(char));
	strncpy(extension, &OUTPUT[strlen(OUTPUT)-6], 6);
	if(strncmp(".trace", extension, 6)){
		printf("\nError: Output file needs *.trace extension. Aborting.\n\n");
		return 0;
	} // Make sure output file extension is well-formed
	free(extension);

	if(strcmp(SMART_GEN, "true") && strcmp(SMART_GEN, "false")){
		printf("\nError: Smart generation parameter should be bool. Aborting.\n\n");
		return 0;
	} // Confirm SMART_GEN parameter is a boolean value

	return 1; // If everything goes okay; return TRUE
}


