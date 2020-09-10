
// Andrew West - gen_utils.h - Header file for gen_utils.c

#ifndef GEN_UTILS_H
#define GEN_UTILS_H

// -------------------------- LOCAL INCLUDES --------------------------------

#include <math.h>

// ------------------------- GLOBAL VARIABLES -------------------------------

float ZIPF_SUM;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

void generate_user_lib(User_Library* ulib);
void generate_file_lib(Network* nw);

float get_zipf(int rank);
int inverse_zipf(float weight);

void generate_transaction_naive(Network* nw);
void generate_transaction_smart(Network* nw);

#endif

