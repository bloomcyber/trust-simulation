
// Andrew West - lib_file.c - Abstraction of file behavior

// -------------------------- LOCAL INCLUDES --------------------------------

#include "globals.h"

// -------------------------- MEMORY ALLOCATION -----------------------------

File_Library* allocate_file_lib(){
	File_Library* flib = (File_Library*) malloc(sizeof(File_Library));
	flib->files = (File*) calloc(NUM_FILES, sizeof(File));
	if(flib == NULL || flib->files == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allocate File_Library pointer and File array
	
	int i;
	for(i=0; i < NUM_FILES; i++){
		flib->files[i].head_node = malloc(sizeof(Owner_Node));
		flib->files[i].tail_node = malloc(sizeof(Owner_Node));
		if(flib->files[i].head_node == NULL || flib->files[i].head_node == NULL){
			printf("\nMemory allocation failed. Aborting.\n\n");
			exit(1);
		} // Allocate head and tail node for all files
	} // Setup individual files
	return flib;
}

// ------------------------ INITIALIZATION FUNCS ----------------------------

void initialize_file_lib(File_Library* flib){
	int i;
	for(i=0; i < NUM_FILES; i++){		
		flib->files[i].num_owners = 0;
		flib->files[i].head_node->next = flib->files[i].tail_node;
	} // Initialization sets one value, hooks up linked-list nodes
	return;
}

// ------------------------ FILE LIST MAINTENANCE ---------------------------

int avail_files(File_Library* flib){
	int i, return_val = 0;
	for(i=0; i < NUM_FILES; i++){
		if(flib->files[i].num_owners > 0)
			return_val++;
	} // Count number of files with at least one owner
	return return_val;
}

int has_file(File_Library* flib, int user, int file_num){          
	Owner_Node* cur_node = flib->files[file_num].head_node->next;
	while(cur_node != flib->files[file_num].tail_node){
		if(user == cur_node->owner)
			return 1;
		cur_node = cur_node->next;
	} // Iterate over file linked-list searching for owner
	return 0;
}

int valid_file(File_Library* flib, int user, int file_num){
	Owner_Node* curNode = flib->files[file_num].head_node->next;
	while(curNode != flib->files[file_num].tail_node){
		if(user == curNode->owner)
			return curNode->is_valid;
		curNode = curNode->next;
	} // Iterate over owner linked-list for file
	return 0;	
}

