
// Andrew West - sim_malicious.h - Header file for sim_malicious.c

#ifndef SIM_MALICIOUS_H
#define SIM_MALICIOUS_H

// -------------------------- LOCAL INCLUDES --------------------------------

typedef enum{
	NAIVE,
	ISOLATED,
	COLLECTIVE
} mal_t;

// ------------------------ STRUCTS & DATATPYPES ----------------------------


// ------------------------ FUNCTION PROTOTYPES -----------------------------

void malicious_compute_trust(Network* nw, int recv, int cycle);

void malicious_vector_set_fback(Network* nw, feedback_t FT, int vec);


#endif
