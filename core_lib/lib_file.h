
// Andrew West - lib_file.h - Header file for lib_file.c

#ifndef LIB_FILE_H
#define LIB_FILE_H

// -------------------------- LOCAL INCLUDES --------------------------------

#include "globals.h"

// ------------------------ STRUCTS & DATATPYPES ----------------------------

typedef struct Owner_Node{
	int owner;
	int is_valid;
	struct Owner_Node* next;
} Owner_Node;

typedef struct{
	int num_owners; 
	Owner_Node* head_node;
	Owner_Node* tail_node;
} File;

typedef struct{
	File* files;
} File_Library;

// ------------------------ FUNCTION PROTOTYPES -----------------------------

File_Library* allocate_file_lib();
void initialize_file_lib(File_Library* flib);

int avail_files(File_Library* lib);
int has_file(File_Library* lib, int user, int file_num);
int valid_file(File_Library* flib, int user, int file_num);

#endif

