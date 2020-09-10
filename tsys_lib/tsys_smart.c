
// Andrew West -tsys_tnasl.c - Abstraction of Subjective Logic trust sytem

// ---------------------------- LOCAL INCLUDES -------------------------------

#include "sim_globals.h"

// -------------------------- GLOBAL VARIABLES -------------------------------

Opinionsmart* vectorA;
Opinionsmart* vectorB;
Opinionsmart* max_vec;
Opinionsmart** op_stor;

// -------------------------- HIGH-LEVEL FUNCTIONS ---------------------------

void smart_compute_trust(Network* nw, int user, int cycle){
	if(cycle == 0)
		smart_initialize(nw->ulib);
	else // Intialize on first call
		smart_master(nw->ulib, user);
	return; // Compute trust thereafter
}

void smart_update(Network* nw, int vec, int row){
	int pos = *nw->ulib->users[vec].vector[row].pos;
	int neg = *nw->ulib->users[vec].vector[row].neg;
	//printf("%d  --  %d\n", pos, neg);
	op_stor[row][vec].b = (pos/(pos + neg + 2.0));
	op_stor[row][vec].d = (neg/(pos + neg + 2.0));
	/*op_stor[row][vec].t = (op_stor[row][vec].b - op_stor[row][vec].d)/(op_stor[row][vec].b + op_stor[row][vec].d);
	if(op_stor[row][vec].t <= 0.0) {
		op_stor[row][vec].a = 1.0; //fabs(a - b) <= FLT_EPSILON
	} 
	else {
		op_stor[row][vec].a = 0.0;
	}*/
	op_stor[row][vec].u = (1.0 - op_stor[row][vec].b - op_stor[row][vec].d);
	//op_stor[row][vec].u = (2.0/(pos + neg + 2.0));
	return;
}

// ----------------------------- TRUST HELPERS -------------------------------

void smart_initialize(User_Library* ulib){
	
	op_stor = (Opinionsmart**) calloc(NUM_USERS, sizeof(Opinionsmart*));
	if(op_stor == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allocate persistent Opinion storage
	
	int i, j;
	for(i=0; i < NUM_USERS; i++){
		op_stor[i] = (Opinionsmart*) calloc(NUM_USERS, sizeof(Opinionsmart));
		if(op_stor[i] == NULL){
			printf("\nMemory allocation failed. Aborting.\n\n");
			exit(1);
		} // Allocate row dimension of the matrix
	} // Allocate persistent Opinion storage
	
	vectorA = (Opinionsmart*) calloc(NUM_USERS, sizeof(Opinionsmart));
	vectorB = (Opinionsmart*) calloc(NUM_USERS, sizeof(Opinionsmart));
	max_vec = (Opinionsmart*) calloc(NUM_USERS, sizeof(Opinionsmart));
	if(vectorA == NULL || vectorB == NULL || max_vec == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allocate scratch space storage for multiplication
	
	for(i=0; i < NUM_USERS; i++){
		for(j=0; j < NUM_USERS; j++){
			op_stor[i][j].b = 0.0;
			op_stor[i][j].d = 0.0;
			op_stor[i][j].u = 1.0;		
			if(ulib->users[i].pre_trusted)
				op_stor[i][j].a = 1.0;
			else
				op_stor[i][j].a = 0.5;
		} // Initialize persistent Opinion values
	}  // Do so for every relation in the network
	return;
}

void smart_master(User_Library* ulib, int user){
	int i, j;
	for(i=0; i < NUM_USERS; i++){
		sop_assign(&max_vec[i], &op_stor[i][user]);
	} // Initialize the 'max value' vector for this run
	
	int cont_mult = smart_multiply(max_vec, op_stor, vectorA);
	while(cont_mult){
		if(!smart_multiply(vectorA, op_stor, vectorB))
			break;
		cont_mult = smart_multiply(vectorB, op_stor, vectorA);
	}  // Multiply until 'max_vector' is saturated
	
	for(i=0; i < NUM_USERS; i++){
		ulib->users[user].vector[i].trust_val = sop_ev(&max_vec[i]);
	} // Export Opinion expected values's as trust values
	return;
}

int smart_multiply(Opinionsmart* vec, Opinionsmart** matrix, Opinionsmart* dest){
	int i, j;
	Opinionsmart op_holder;
	for(i=0; i < NUM_USERS; i++){
		for(j=0; j < NUM_USERS; j++){
			if(j == 0)
				sop_discount(&vec[0], &matrix[i][0], &dest[i]);
			else{
				sop_discount(&vec[j], &matrix[i][j], &op_holder);
				sop_consensus(&dest[i],&op_holder, &dest[i]);
			} // Don't consensus first discount; it isn't monotonic
		} // Inner loop of matrix-vector multiplication
	} // Outer loop of matrix-vector multiplication
	
	int max_modified = 0;
	for(i=0; i < NUM_USERS; i++){
		if(sop_compare(&dest[i], &max_vec[i]) == 1){
			sop_assign(&max_vec[i], &dest[i]);
			max_modified = 1;
		} // Flag flips if a copy to 'max_vec' is made
	} // Update the 'max_value' vector at each position
	return max_modified;
}

// --------------------------- OPINION FUNCTIONS ----------------------------

void sop_discount(Opinionsmart* op1, Opinionsmart* op2, Opinionsmart* dest){	
	dest->b = op1->b * op2->b;
	dest->d = op1->b * op2->d;
	dest->u = (1.0 - dest->b - dest->u);
	//dest->u = op1->d + op1->u + (op1->b * op2->u);
	dest->a = op2->a;
	return;
}

void sop_consensus(Opinionsmart* op1, Opinionsmart* op2, Opinionsmart* dest){
	if((op1->u == 0.0) && (op2->u == 0.0)){
		dest->b = (op1->b + op2->b) / 2.0;
		dest->d = (1.0 - dest->b);
		//dest->d = (op1->d + op2->d) / 2.0;
		dest->u = 0.0;
	} else{
		float denom = (op1->u + op2->u) - (op1->u * op2->u);
		dest->b = ((op1->b * op2->u) + (op2->b * op1->u)) / denom;
		dest->d = ((op1->d * op2->u) + (op2->d * op1->u)) / denom;
		dest->u = (1.0 - dest->b - dest->u);
		//dest->u = (op1->u * op2->u) / denom;
	} // Math differs based on uncertainty values
	dest->a = op1->a;
	return;
}

float sop_ev(Opinionsmart* op){
	float b, d, at, t;	
	
	b = op->b;
	d = op->d;
	if((b+d) > 0) {
		t = (b-d)/(b+d);
	}
	else {
		t = 0;
	}
	if(t < -0.4) {
		at = 1.0; //fabs(a - b) <= FLT_EPSILON
	} 
	else {
		at = 0.0;
	}
	t = t - at;
	op->t = t;
	//printf("%f\n",op->t);
	return op->t;
}

void sop_assign(Opinionsmart* op1, Opinionsmart* op2){
	op1->b = op2->b;
	op1->d = op2->d;
	op1->u = op2->u;
	op1->a = op2->a;
	return;
}

int sop_compare(Opinionsmart* this, Opinionsmart* that){
	if(this->u < that->u)
		return (1);
	else if(this->u > that->u)
		return (-1);
	else{
		if(this->b > that->b)
			return (1);
		else if(this->b < that->b)
			return (-1);
		else
			return 0;
	} // Compare first by confidence, ties broken by belief.
}

