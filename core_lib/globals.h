
// Andrew West - globals.h - Global header file for the P2P Simulator

#ifndef GLOBALS_H
#define GLOBALS_H

// -------------------------- ANSI-C INCLUDES -------------------------------

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <float.h>

// -------------------------- LOCAL INCLUDES --------------------------------

#include "globals.h"
#include "lib_network.h"
#include "lib_file.h"
#include "lib_user.h"
#include "lib_bwidth.h"
#include "lib_relation.h"
#include "lib_delay.h" 

// ----------------------------- MACROS -------------------------------------

  // Compute a random floating point number on [0, 1]
#define RAND_FP() ((double)rand()/((double)(RAND_MAX)+(double)(1)))

// ------------------------- GLOBAL VARIABLES -------------------------------

extern int NUM_USERS; // # of peers in the network
extern int NUM_FILES; // # of distinct files in network
extern int NUM_TRANS; // # of transactions to simulate

extern int PRE_TRUSTED; // # of pre-trusted users, a subset of 'good' 

extern int BAND_MAX; // # of max upload/download connections per user
extern int BAND_PER; // # of time units each upload/download requires

extern int WARMUP;     // # of warmup insns before statistical tabulation
extern long RAND_SEED; // Seed initializing event randomness

#endif

