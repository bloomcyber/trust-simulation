
// Andrew West - tsys_eigen.c - Abstraction of EigenTrust system

// ---------------------------- LOCAL INCLUDES -------------------------------

#include "sim_globals.h"

// -------------------------- GLOBAL VARIABLES -------------------------------

const float ALPHA = 0.5;
const float EPSILON = 0.001;

float* pretrust;
float* vectorA;
float* vectorB;
float** normals;

float* scratch_vec;

// ------------------------- HIGH-LEVEL TRUST CALLS -------------------------

void eigen_compute_trust(Network* nw, int user, int cycle){
	if(cycle == 0)
		eigen_initialize(nw->ulib);
	else // Setup infrastructure on first call
		eigen_trust_multiply(nw->ulib, user, 8); // Compute trust thereafter
	return;
}

void eigen_update(Network* nw, int new_vec, int new_row){
	eigen_normalize_vector(nw->ulib, new_vec);
	return;
}

// ----------------------------- TRUST HELPERS ------------------------------

void eigen_initialize(User_Library* ulib){
	
	pretrust = (float*) calloc(NUM_USERS, sizeof(float));
	vectorA = (float*) calloc(NUM_USERS, sizeof(float));
	vectorB = (float*) calloc(NUM_USERS, sizeof(float));
	normals = (float**) calloc(NUM_USERS, sizeof(float*));
	if(pretrust == NULL || vectorA == NULL || vectorB == NULL || normals == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allocate 2-D pointer setup for normalization/multiplication matrices
	
	scratch_vec = (float*) calloc(NUM_USERS, sizeof(float));
	if(scratch_vec == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Setup some buffer space to avoid constant re-allocation
	
	int i, j;
	for(i=0; i < NUM_USERS; i++){
		normals[i] = (float*) calloc(NUM_USERS, sizeof(float));
		if(normals[i] == NULL){
			printf("\nMemory allocation failed. Aborting.\n\n");
			exit(1);
		} // Allocate row dimension of the matrix
	} // Create simple matrix to store normalized vals
	
	for(i=0; i < NUM_USERS; i++){
		if((PRE_TRUSTED > 0) && (ulib->users[i].pre_trusted))
			pretrust[i] = (1.0 / PRE_TRUSTED);
		else if(PRE_TRUSTED > 0) // and not pre-trusted
			pretrust[i] = 0.0;
		else // (there are no pre-trusted users)
			pretrust[i] = (1.0 / NUM_USERS);
		
		for(j=0; j < NUM_USERS; j++)
			normals[i][j] = pretrust[i];
	}  // Setup the persistent normalized and pre-trusted structs
	return;
}

void eigen_normalize_vector(User_Library* ulib, int new_vec){
	int i, fback_int;
	int normalizer = 0;
	for(i=0; i < NUM_USERS; i++){
		fback_int = eigen_fback_int(&ulib->users[new_vec].vector[i]);
		normalizer += fback_int;
		normals[i][new_vec] = fback_int;
	} // Calculate normalizing sum in first pass

	if(normalizer == 0){
		for(i=0; i < NUM_USERS; i++)
			normals[i][new_vec] = pretrust[i];
	} else{ // If a user trusts no one, default to the pre_trust vector
		for(i=0; i < NUM_USERS; i++)
			normals[i][new_vec] /= (normalizer*1.0);
	} // Else, do the normalizing division in a second pass

	return;
}

float* eigen_trust_multiply(User_Library* ulib, int user, int max_iters){
	eigen_single_multiply(pretrust, vectorA);
	max_iters--;
	do{ // Multiply until convergence or maximum iters reached
		eigen_single_multiply(vectorA, vectorB);
		eigen_single_multiply(vectorB, vectorA);
		max_iters -= 2;
	} while((max_iters > 0) && !eigen_converged(vectorA, vectorB));
		
	int i;
	for(i=0; i < NUM_USERS; i++){
		ulib->users[user].vector[i].trust_val = vectorA[i];
	} // Import trust values back into Object form 
	return vectorA;
}

void eigen_single_multiply(float* source_vec, float* dest_vec){	
	lalg_vector_matrix_mult(source_vec, normals, scratch_vec);
	lalg_constant_vector_mult((1-ALPHA), scratch_vec, scratch_vec);
	lalg_constant_vector_mult(ALPHA, pretrust, dest_vec);
	lalg_vector_add(scratch_vec, dest_vec, dest_vec);
	return;
}

int eigen_converged(float* vec1, float* vec2){
	int i;
	for(i=0; i < NUM_USERS; i++){
		if(abs(vec1[i]-vec2[i]) > EPSILON)
			return 0;
	} // Compare vector elements, examining delta change
	return 1;
}

int eigen_fback_int(Relation* rel){
	int fback_int = *rel->pos - *rel->neg;
	if(fback_int < 0)
		fback_int = 0;
	return fback_int;
}

// -------------------------- LINEAR ALGEBRA STUFF --------------------------

void lalg_vector_matrix_mult(float* vector, float** matrix, float* dest_vec){
	int i,j;
	for(i=0; i < NUM_USERS; i++){
		dest_vec[i] = 0.0;
		for(j=0; j < NUM_USERS; j++){
			dest_vec[i] += (matrix[i][j] * vector[j]);
		} // Inner loop of matrix-vector multiplication
	} // Outer loop of matrix-vector multiplication
	return;
}

void lalg_constant_vector_mult(float constant, float* vector, float* dest_vec){
	int i;
	for(i=0; i < NUM_USERS; i++){
		dest_vec[i] = vector[i] * constant;
	} // Just multiply every vector element by the constant
	return;
}

void lalg_vector_add(float* vector1, float* vector2, float* dest_vec){
	int i;
	for(i=0; i < NUM_USERS; i++){
		dest_vec[i] = vector1[i] + vector2[i];
	} // Just add the elements at correspondong positions
	return;
}


