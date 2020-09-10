
// Andrew West - gen_utils.c - Abstraction of trace generator behavior

// -------------------------- LOCAL INCLUDES --------------------------------

#include "gen_globals.h"
#include <math.h>

// --------------------- LIB GENERATION FUNCTIONS ---------------------------

void generate_user_lib(User_Library* ulib){
	int count = 0, good_inited = 0;
	int terminate = count + USR_PURE;
	for(count=0; count < terminate; count++)
		initialize_user(&ulib->users[count], BEHAVE_PURE, 0);
	terminate = count + USR_FEED;
	for(count; count < terminate; count++)
		initialize_user(&ulib->users[count], BEHAVE_FEED, 0);
	terminate = count + USR_PROV;
	for(count; count < terminate; count++)
		initialize_user(&ulib->users[count], BEHAVE_PROV, 0);
	terminate = count + USR_DISG;
	for(count; count < terminate; count++)
		initialize_user(&ulib->users[count], BEHAVE_DISG, 0);
	terminate = count + USR_SYBL;
	for(count; count < terminate; count++)
		initialize_user(&ulib->users[count], BEHAVE_SYBL, 0);
	for(count; count < NUM_USERS; count++){
		if(good_inited < PRE_TRUSTED)
			initialize_user(&ulib->users[count], BEHAVE_GOOD, 1);
		else
			initialize_user(&ulib->users[count], BEHAVE_GOOD, 0);
		good_inited++;
	} // A subset of good users should be init-ed as pre-trusted
	return;
}

void generate_file_lib(Network* nw){
	int valid, i, j;
	for(i=0; i < NUM_USERS; i++){
		for(j=0; j < NUM_FILES; j++){
			if(RAND_FP() <= get_zipf(j)){
				valid = (RAND_FP() <= nw->ulib->users[i].pct_cleanup);
				print_file(i, j, valid);
				add_file(nw, i, j, (int) NULL);
			} // Add file to library if over parameter threshold
		} // Each user can (probabilistically) own any file
	} // Initialize libraries for all users
	for(i=0; i < NUM_FILES; i++){
		ZIPF_SUM += get_zipf(i);
	} // Calculate total ZIPF weight for all files
	AV_FILES = avail_files(nw->flib);
	fprintf(out, "\n");
	return;
}

// ---------------------------- ZIPF FUNCTIONS -------------------------------

float get_zipf(int rank){
	return ((1.0) / (powf((rank + 2.0), ZIPF)));
}

int inverse_zipf(float weight){
	int i;
	float total = 0.0;
	for(i=0; i < NUM_FILES; i++){
		total += get_zipf(i);
		if(total > weight)
			return i;
	} // Iteratively sum frequencies
	return (NUM_FILES-1);
}

// ------------------------- TRANSACTION FUNCTIONS ---------------------------

// There are two approaches to transaction generation. First, we can let any
// user request any file with no guarantees in place. On the simulator end,
// this means many "incomplete but not invalid" transactions will be seen.
void generate_transaction_naive(Network* nw){
	int recv = (int) (RAND_FP() * NUM_USERS);
	int file_num = (int) (RAND_FP() * NUM_FILES);
	print_trans(recv, file_num);
	return;
}

// Or secondly, we can make the guarantee that a user will never request a file
// they already possess (or once possessed), and that SOMEONE owns the
// requested file (though they might not be able to provide due to bandwidth).
void generate_transaction_smart(Network* nw){
	int recv, file_num;
	
	do{ // A receiver shouldn't already have a "full" library
		recv = (int) (RAND_FP() * NUM_USERS);
	} while((nw->ulib->users[recv].num_files) == AV_FILES);
	
	int cond1, cond2;
	do{ // Receiver must not already have file, and it must be available
		file_num = inverse_zipf(RAND_FP() * ZIPF_SUM);
		cond1 = has_file(nw->flib, recv, file_num);
		cond2 = nw->flib->files[file_num].num_owners == 0;
	} while(cond1 || cond2);
	
	add_file(nw, recv, file_num, (int) NULL);
	print_trans(recv, file_num);
	return;
}

