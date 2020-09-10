
// Andrew West - sim_globals.h - Glober header for simulator half of P2P-Sim

#ifndef SIM_GLOBALS_H
#define SIM_GLOBALS_H

// -------------------------- LOCAL INCLUDES --------------------------------

#include "globals.h"
#include "sim_parse.h"
#include "sim_trans.h"
#include "sim_malicious.h"
#include "sim_source.h"
#include "sim_output.h"

#include "tsys_eigen.h"
#include "tsys_zheyang.h"
#include "tsys_smart.h"
#include "tsys_etinc.h"
#include "tsys_tnasl.h"
#include "tsys_block.h"
#include "tsys_none.h"


// ------------------------ STRUCTS & DATATPYPES ----------------------------

typedef enum{
  NONE,
	BLOCK,
	ZHEYANG,	
	EIGEN,
	SMART,
	ET_INC,
	TNA_SL
} trust_alg_t;

// ------------------------- GLOBAL VARIABLES -------------------------------

extern trust_alg_t TSYS;      // Trust system employed by this simulation run
extern mal_t STRATEGY;				// Malicious strategy being employed

extern FILE* out;             // Filestream to output file (write permission)
extern FILE* in;              // Filestream to input file (read permissions)

extern char* FILE_NAME;       // Filename of file about to be opened/closed
extern char cur_line[100];    // Buffer where in-read lines are stored
extern char scratch_str[100]; // Extra buffer to help in string manipulation
extern Transaction trans_ex;  // Transaction buffer for passing around data

extern int* collective;				// Array holding user ID's of collective members
extern int mal_count;					// The number of members in above array

extern int NUM_INVAL_TRANS;   // # of invalid transactions completed
extern int NUM_RECV_BLK_TR;   // # of transactions prevented at receiver-level
extern int NUM_SEND_BLK_TR;   // # of transactions lost due to lack of source
extern int NUM_FBACK_TRUE;    // # of honest feedbacks comitted
extern int NUM_FBACK_LIES;    // # of dis-honest feedbacks comitted
extern int NUM_FBACK_SYBL;    // # of sybil feedbacks "committed"
extern int NUM_GOOD_SUCC;     // # of valid trans initiated by good users
extern int NUM_GOOD_FAIL;     // # of invalid trans initiated by good users

#endif

