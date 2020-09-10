
// Andrew West - lib_network.c - Abstraction of network behavior

// -------------------------- LOCAL INCLUDES --------------------------------

#include "globals.h"

// -------------------------- MEMORY ALLOCATION -----------------------------

Network* allocate_network(){
	Network* nw = (Network*) malloc(sizeof(Network));
	if(nw == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allocate the network
	nw->ulib = allocate_user_lib();
	nw->flib = allocate_file_lib();
	nw->dunit = allocate_delay_unit();
	return nw;
}

// ------------------------ INITIALIZATION FUNCS ----------------------------

void initialize_network(Network* nw){
	initialize_user_lib(nw->ulib);
	initialize_file_lib(nw->flib);
	initialize_delay_unit(nw->dunit);
}

// --------------------------- NETWORK FUNCS --------------------------------

	// add_file() is a method that would better reside in lib_file.c, however
	// user library access is needed in order to increment a counter. While messy,
	// this access has very large efficiency benefits. 
void add_file(Network* nw, int user, int file_num, int valid){
	Owner_Node* new_node = (Owner_Node*) malloc(sizeof(Owner_Node));
	if(new_node == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allocate the new owner node
	new_node->owner = user;
	new_node->is_valid = valid;
	new_node->next = nw->flib->files[file_num].head_node->next;
	nw->flib->files[file_num].head_node->next = new_node;
	nw->flib->files[file_num].num_owners++;
	nw->ulib->users[user].num_files++; // Crucial line
	return;
}

