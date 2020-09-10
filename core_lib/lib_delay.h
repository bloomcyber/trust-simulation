
// Andrew West - lib_delay.h - Header file for lib_delay.c

#ifndef LIB_DELAY_H
#define LIB_DELAY_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------

typedef struct{
	int commit_cycle;
	int send;
	int recv; 
	int file_num;
	int valid;
} Transaction;

typedef struct{
	Transaction* t_queue;
	int push_pointer;
	int pop_pointer;
} Delay_Unit;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

Delay_Unit* allocate_delay_unit();
void initialize_delay_unit(Delay_Unit* dunit);

#endif

