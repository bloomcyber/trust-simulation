
// Andrew West - lib_bwidth.h - Header file for lib_bwidth.c

#ifndef LIB_BWIDTH_H
#define LIB_BWIDTH_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------

typedef struct{
	int* usage_queue;
	int pointer;
} BWidth_Unit;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

BWidth_Unit* allocate_bwidth_unit();
void initialize_bwidth_unit(BWidth_Unit* bwu);

int bwidth_avail(BWidth_Unit* bwu, int cycle);
void bwidth_use(BWidth_Unit* bwu, int cycle);

#endif

