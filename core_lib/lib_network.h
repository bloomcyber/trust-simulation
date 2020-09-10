
// Andrew West - lib_network.h - Header file for lib_network.c

#ifndef LIB_NETWORK_H
#define LIB_NETWORK_H

// -------------------------- LOCAL INCLUDES --------------------------------

#include "lib_user.h"
#include "lib_file.h"
#include "lib_delay.h"

// ------------------------ STRUCTS & DATATPYPES ----------------------------

typedef struct{
	User_Library* ulib;
	File_Library* flib;
	Delay_Unit* dunit;
} Network;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

Network* allocate_network();
void initialize_network(Network* nw);

void add_file(Network* nw, int user, int file_num, int valid);

#endif

