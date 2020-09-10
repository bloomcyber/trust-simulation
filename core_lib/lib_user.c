
// Andrew West - lib_user.c - Abstraction of user behavior

// -------------------------- LOCAL INCLUDES --------------------------------

#include "globals.h"

// -------------------------- MEMORY ALLOCATION -----------------------------

User_Library* allocate_user_lib(){
	User_Library* ulib = (User_Library*) malloc(sizeof(User_Library));
	ulib->users = (User*) calloc(NUM_USERS, sizeof(User));
	if(ulib == NULL || ulib->users == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allocate the network
	int i;
	for(i=0; i < NUM_USERS; i++){
		ulib->users[i].bw_ul = allocate_bwidth_unit();
		ulib->users[i].bw_dl = allocate_bwidth_unit();
		ulib->users[i].vector = allocate_rel_vector();
	}
	return ulib;
}

// ------------------------- LIBRARY INIT FUNCS -----------------------------

void initialize_user_lib(User_Library* ulib){	
	int i;
	for(i=0; i < NUM_USERS; i++)
		initialize_user(&ulib->users[i], UNKNOWN, 0);
	return;
}

// -------------------------- USER INIT FUNCS -------------------------------

void initialize_user(User* user, user_t behavior, int pre_trusted){
	user->num_files = 0;
	user->pre_trusted = pre_trusted;
	switch(behavior){
		case BEHAVE_GOOD:
			user->behavior = BEHAVE_GOOD;
			user->pct_cleanup = 1.0 - (RAND_FP() / 10);
			user->pct_honest = 1.0;
			break;
		case BEHAVE_PURE:
			user->behavior = BEHAVE_PURE;
			user->pct_cleanup = (RAND_FP()/10);
			user->pct_honest = 0.0;
			break;
		case BEHAVE_FEED:
			user->behavior = BEHAVE_FEED;
			user->pct_cleanup = 1.0 - (RAND_FP() / 10);
			user->pct_honest = 0.0;
			break;
		case BEHAVE_PROV:
			user->behavior = BEHAVE_PROV;
			user->pct_cleanup = (RAND_FP() / 10);
			user->pct_honest = 1.0;
			break;
		case BEHAVE_DISG:
			user->behavior = BEHAVE_DISG;
			user->pct_cleanup = 0.5 + (RAND_FP() / 2);
			user->pct_honest = 0.5 + (RAND_FP() / 2);
			break;
		case BEHAVE_SYBL:
			user->behavior = BEHAVE_SYBL;
			user->pct_cleanup = (RAND_FP()/10);
			user->pct_honest = 0.0; // irrelevant
			break;
		case UNKNOWN:
			user->behavior = UNKNOWN;
			user->pct_cleanup = 0.0;
			user->pct_honest = 0.0;
			break;
	} // Select user attributes based on behavior model
	initialize_bwidth_unit(user->bw_ul);
	initialize_bwidth_unit(user->bw_dl);
	int i;
	for(i=0; i < NUM_USERS; i++)
		initialize_rel(&user->vector[i]);
	return;
}

