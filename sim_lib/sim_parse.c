
// Andrew West - sim_parse.c - Abstraction of simulator parsing funcs

// ---------------------------- LOCAL INCLUDES -------------------------------

#include "sim_globals.h"

// --------------------------- PARSING FUNCTIONS -----------------------------

void parse_and_print_globals(){

	int i;
	fprintf(out, "\n----------- TRACE PARAMETERS ---------");
	for(i=0; i<=15; i++){
		fgets(cur_line, 100, in);
		switch(i){
			case 0: NUM_USERS = atoi(cur_line); break;
			case 1: NUM_FILES = atoi(cur_line); break;
			case 2: NUM_TRANS = atoi(cur_line); break;
			case 3: BAND_MAX = atoi(cur_line); break;
			case 4: BAND_PER = atoi(cur_line); break;
			case 5: WARMUP = atoi(cur_line); break;
			case 7: PRE_TRUSTED = atoi(cur_line); break;
			default: break;
		} // Parse variables based solely on order in trace
		
		switch(i){
			case 0: 
				fprintf(out, "\n>Number of Peers:        %d", NUM_USERS); break;
			case 1: 
				fprintf(out, "\n>Number of Files:        %d", NUM_FILES); break;
			case 2: 
				fprintf(out, "\n>Number of Transactions: %d", NUM_TRANS); break;
			case 3: 
				fprintf(out, "\n>Max. User Connections:  %d", BAND_MAX); break;
			case 4: 
				fprintf(out, "\n>Bandwidth Period:       %d", BAND_PER); break;
			case 5: 
				fprintf(out, "\n>Warm-up Transactions:   %d", WARMUP); break;
			case 6:
				fprintf(out, "\n>Zipf Constant:          %f", atof(cur_line)); break;
			case 7:
				fprintf(out, "\n>Pre-Trusted Users:      %d", PRE_TRUSTED); break;
			case 8: 
				fprintf(out, "\n>Good Behaving Users:    %d", atoi(cur_line)); break;
			case 9: 
				fprintf(out, "\n>Purely Malicious Users: %d", atoi(cur_line)); break;
			case 10: 
				fprintf(out, "\n>Feedback Skewing Users: %d", atoi(cur_line)); break;
			case 11: 
				fprintf(out, "\n>Maligned Providers:     %d", atoi(cur_line)); break;
			case 12: 
				fprintf(out, "\n>Disguised Malignants:   %d", atoi(cur_line)); break;
			case 13: 
				fprintf(out, "\n>Sybil Attackers:        %d", atoi(cur_line)); break;
			case 14: 
				fprintf(out, "\n>Smart Trans Gen?:       %s", atow(cur_line)); break;
			case 15: 
				fprintf(out, "\n>Generator Rand Seed:    %ld", atol(cur_line)); break;
			default: break;
		} // Another switch statement handles printing output header
	} // A loop iterates over lines in the input file
	fgets(cur_line, 100, in); // Read off separator line
	
		// Tack on some additonal lines to the output file
	fprintf(out, "\n>Simulator Rand Seed:    %d\n\n", RAND_SEED);
	fprintf(out, "---------- SIMULATOR SPECIFIC --------");
	fprintf(out, "\n>Simulator used:         %s", output_tsys());
	fprintf(out, "\n>Malicious strategy:     %s\n\n", output_strategy());
			
	return;
} 

void parse_users(User_Library* ulib){
	int i; char* index;
	for(i=0; i < NUM_USERS; i++){
		fgets(cur_line, 100, in);		
		strncpy(scratch_str, &cur_line[1], strlen(cur_line));
			ulib->users[i].pct_cleanup = atof(scratch_str);
		index = strstr(scratch_str, ",") + 1;
		strncpy(cur_line, index, strlen(scratch_str));
			ulib->users[i].pct_honest = atof(cur_line);
		index = strstr(cur_line, ",") + 1;
		strncpy(scratch_str, index, strlen(cur_line));
			ulib->users[i].behavior = (user_t) atoi(scratch_str);
		index = strstr(cur_line, ",") + 1;
		strncpy(scratch_str, index, strlen(cur_line));
			ulib->users[i].pre_trusted = parse_bool(scratch_str);
	} // We expect 'NUM_USERS' lines of data
	fgets(cur_line, 100, in); // Read off blank seperator
	return;
}

void parse_file_libs(Network* nw){
	char* index;
	int user, file_num, valid;
	fgets(cur_line, 100, in);
	while(strlen(cur_line) > 1){
		strncpy(scratch_str, &cur_line[1], strlen(cur_line));
			user = atoi(scratch_str);
		index = strstr(scratch_str, ",") + 1;
		strncpy(cur_line, index, strlen(scratch_str));
			file_num = atoi(cur_line);
		index = strstr(cur_line, ",") + 1;
		strncpy(scratch_str, index, strlen(cur_line));
			valid = parse_bool(scratch_str);
		add_file(nw, user, file_num, valid);
		fgets(cur_line, 100, in);
	} // Parse all lines pertaining to file libraries, add files accordingly
	return;
}

void parse_next_trans(){
	fgets(cur_line, 100, in);
	strncpy(scratch_str, &cur_line[1], strlen(cur_line));
		trans_ex.recv = atoi(scratch_str);
	char* index = strstr(scratch_str, ",") + 1;
	strncpy(cur_line, index, strlen(scratch_str));
		trans_ex.file_num = atoi(cur_line);
	return;
}

// ---------------------------- PARSING HELPERS ------------------------------

  // Crude, but effective. Use carefully
int parse_bool(char* string){
	if(strstr(string, "true") != NULL)
		return 1;
	else
		return 0;
}

	// Similar in vein to the other ato* standard C methods, given a string, this
	// function returns the first space delimited word in the string (in place).
char* atow(char* string){
	char* halt = strchr(string, ' ');
	int length= ((halt-string)/sizeof(char));
	string[length] = '\0';
	return string;
}

