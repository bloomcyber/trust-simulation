
// Andrew West - gen_globals.h - Glober header for generator half of P2P-Sim

#ifndef GEN_GLOBALS_H
#define GEN_GLOBALS_H

// -------------------------- LOCAL INCLUDES --------------------------------

#include "globals.h"
#include "gen_utils.h"
#include "gen_output.h"

// ------------------------- GLOBAL VARIABLES -------------------------------

extern float ZIPF;			// Zipf constant controlling file popularity 
extern char* OUTPUT;    // Filename for trace output

extern int USR_GOOD;    // # of well-behaved users
extern int USR_PURE;    // # of "purely malicious" users
extern int USR_FEED;    // # of "1-D, feedback skewing" users
extern int USR_PROV;    // # of "1-D, bad provider" users
extern int USR_DISG;    // # of "disguised malicious" users
extern int USR_SYBL;    // # of "Sybil attack" users

extern char* SMART_GEN; // Intelligent transaction generation? (bool)
extern FILE* out;       // Filestream to output file (write permission)

extern int AV_FILES;    // # of available files in network

#endif

