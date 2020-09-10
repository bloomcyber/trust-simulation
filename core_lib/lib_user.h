
// Andrew West - lib_user.h - Header file for lib_user.c

#ifndef LIB_USER_H
#define LIB_USER_H

// -------------------------- LOCAL INCLUDES --------------------------------

#include "lib_bwidth.h"
#include "lib_relation.h"

// ------------------------ STRUCTS & DATATPYPES ----------------------------

typedef enum{
  BEHAVE_GOOD,
  BEHAVE_PURE,
  BEHAVE_FEED,
	BEHAVE_PROV,
	BEHAVE_DISG,
	BEHAVE_SYBL,
	UNKNOWN
} user_t;

typedef struct{
	user_t behavior;
	int pre_trusted;
	int num_files;
	float pct_cleanup;
	float pct_honest;
	BWidth_Unit* bw_ul;
	BWidth_Unit* bw_dl;
	Relation* vector;
} User;

typedef struct{
	User* users;
} User_Library;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

User_Library* allocate_user_lib();
void initialize_user_lib(User_Library* ulib);
void initialize_user(User* user, user_t behavior, int pre_trusted);

#endif

