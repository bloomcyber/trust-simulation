
// Andrew West -tsys_tnasl.c - Abstraction of Subjective Logic trust sytem

// ---------------------------- LOCAL INCLUDES -------------------------------

#include "sim_globals.h"
#include "math.h"
// -------------------------- GLOBAL VARIABLES -------------------------------

Opinionb* vectorA;
Opinionb* vectorB;
Opinionb* max_vec;
Opinionb** op_stor;
int count; //to know the number of trusted users - venkat
float fm, fn;
float theta1, theta2;
int a[1000][1000];
float t[1000], ts; //to avoid duplicate votes - venkat
// -------------------------- HIGH-LEVEL FUNCTIONS ---------------------------

void block_compute_trust(Network* nw, int user, int cycle){
	if(cycle == 0) {
		//printf("Cycle %d\n",cycle);
		block_initialize(nw->ulib);
	}
	else { // Intialize on first call
		//printf("Cycle %d\n",cycle);
		block_master(nw->ulib, user);
	}
	return; // Compute trust thereafter
}

/*void block_update(Network* nw, int vec, int row){
	int pos = *nw->ulib->users[vec].vector[row].pos;
	int neg = *nw->ulib->users[vec].vector[row].neg;	
	printf("%d -- %d\n", vec, a[vec]);
	if(neg == 0 && pos > 0 && a[vec] == 0) {
		op_stor[vec][vec].b = op_stor[vec][vec].b + 1.0;
		a[vec] = 1;
		op_stor[row][vec].d = 0; //not required - venkat
		op_stor[row][vec].u = 0;//not required - venkat
		printf("%d --  %d   %f\n",pos,neg,op_stor[vec][vec].b);
		//printf("%s\n","pos");
		//exit(0);
	}
	else {
		a[vec] = 0;
		op_stor[vec][vec].b = 0;
		op_stor[row][vec].d = 0;//not required - venkat
		op_stor[row][vec].u = 0;//not required - venkat
		//printf("%d   %d   %f\n",pos,neg,op_stor[row][row].b);
		//printf("%s\n","neg");
	}
	//op_stor[row][vec].b = (pos/(pos + neg + 2.0));
	//op_stor[row][vec].d = (neg/(pos + neg + 2.0));
	//op_stor[row][vec].u = (1.0 - op_stor[row][vec].b - op_stor[row][vec].d);
	//op_stor[row][vec].u = (2.0/(pos + neg + 2.0));
	
	return;
}*/

void block_update(Network* nw, int vec, int row){
	int pos = *nw->ulib->users[vec].vector[row].pos;
	int neg = *nw->ulib->users[vec].vector[row].neg;
	int i,p;	
	fm = pos;	
	fn = neg;	
	if (pos > neg) {
		fm = pow(pos,2);
	}
	else {
		fn = pow(neg,2);
	}
	//printf("%d--%d--%f--%f--%f\n",fm,fn,theta1, theta2, ts);
	if (fm>=1) {theta1 = fm/(fm + fn);} else theta1 =0;
	if (fn>=1) {theta2 = fn/(fm + fn);} else theta2 =0;
	//printf("%d--%d--%f--%f\n",fm,fn,theta1, theta2);
	if (pos != 0 || neg !=0) {
		ts = ((theta1*(float)pos) - (theta2*(float)neg))/(float)(pos + neg);
		p = (int)ts;
			//op_stor[row][vec].d = 0; //not required - venkat
		//op_stor[row][vec].u = 0;//not required - venkat
	}
	else {
		ts = 0.0;
		p = (int)ts;
	}
	//printf("%f %d\n", ts, p);
	if (p > 0) {
		if(a[vec][row] == 0) {
			a[vec][row] = 1;
			//op_stor[row][vec].b = op_stor[row][vec].b + 1;
			t[vec] = t[vec] + 1;
			//for(i=0; i < NUM_USERS; i++){
			//	op_stor[i][vec].b = op_stor[i][vec].b + 1;		
			//}
		}
	}
	else {
		//op_stor[row][vec].b = 0;
		t[vec] = 0;
		for(i=0; i < NUM_USERS; i++){
			//op_stor[i][vec].b = 0;			
			a[vec][i] = 0;
		}
		
	}
	//printf("%d  %d  %d   %d  %f %f %f  %f %f %f \n",vec,row,pos,neg,fm,fn,theta1, theta2, ts, t[vec]);
	/*

	if(pos > 0) {
		op_stor[vec][vec].b = op_stor[vec][vec].b + 1.0;
		//a[row] = 1;
		//t[row] = t[row] + 1;
		//op_stor[row][vec].d = 0; //not required - venkat
		//op_stor[row][vec].u = 0;//not required - venkat
		//printf("%d --  %d   %f\n",pos,neg,op_stor[vec][vec].b);
		//printf("%s\n","pos");
		//exit(0);
	}
	if(neg > 0) {
		//float threshold = ((NUM_USERS/2)/100.0)*40;
		//if (t[row] >= threshold) { 
		//	t[row] = 0;
		op_stor[vec][vec].b = 0.0;
		//	for(i=0; i < NUM_USERS; i++){
		//		a[i] = 0;
		//	}
		//}
		//op_stor[vec][vec].b = 0;
		//op_stor[row][vec].d = 0;//not required - venkat
		//op_stor[row][vec].u = 0;//not required - venkat
		//printf("%d   %d   %f\n",pos,neg,op_stor[row][row].b);
		//printf("%s\n","neg");
	}
	//op_stor[row][vec].b = (pos/(pos + neg + 2.0));
	//op_stor[row][vec].d = (neg/(pos + neg + 2.0));
	//op_stor[row][vec].u = (1.0 - op_stor[row][vec].b - op_stor[row][vec].d);
	//op_stor[row][vec].u = (2.0/(pos + neg + 2.0));
	//for(i=0; i < NUM_USERS; i++){
	//	nw->ulib->users[vec].vector[i].trust_val = t[vec];
	//}
	//printf("%d  %d  %d   %d  %d %d %f  %f \n",vec,row,pos,neg,m, a[row],t[vec],nw->ulib->users[vec].vector[i-1].trust_val);
	*/
	return;
}

// ----------------------------- TRUST HELPERS -------------------------------

void block_initialize(User_Library* ulib){
	
	op_stor = (Opinionb**) calloc(NUM_USERS, sizeof(Opinionb*));
	if(op_stor == NULL){
		printf("\nMemory allocation failed. Aborting.\n\n");
		exit(1);
	} // Allocate persistent Opinion storage
	
	int i, j;
	for(i=0; i < NUM_USERS; i++){
		t[i] = 0;
		for(j=0; j < NUM_USERS; j++){
			a[i][j] = 0;
		}
	}
	for(i=0; i < NUM_USERS; i++){
		op_stor[i] = (Opinionb*) calloc(NUM_USERS, sizeof(Opinionb));
		if(op_stor[i] == NULL){
			printf("\nMemory allocation failed. Aborting.\n\n");
			exit(1);
		} // Allocate row dimension of the matrix
	} // Allocate persistent Opinion storage
	
	vectorA = (Opinionb*) calloc(NUM_USERS, sizeof(Opinionb));
	vectorB = (Opinionb*) calloc(NUM_USERS, sizeof(Opinionb));
	max_vec = (Opinionb*) calloc(NUM_USERS, sizeof(Opinionb));
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

void block_master(User_Library* ulib, int user){
	int i, j;
	//for(i=0; i < NUM_USERS; i++){
	//	bop_assign(&max_vec[i], &op_stor[i][user]);
	//} // Initialize the 'max value' vector for this run
	
	//int cont_mult = tnasl_multiply(max_vec, op_stor, vectorA);
	//while(cont_mult){
	//	if(!tnasl_multiply(vectorA, op_stor, vectorB))
	//
	//
	//		break;
	//	cont_mult = tnasl_multiply(vectorB, op_stor, vectorA);
	//}  // Multiply until 'max_vector' is saturated
	
	//printf("%d--------------->   ", user);
	float threshold = ((NUM_USERS/2)/100.0)*40;
	for(i=0; i < NUM_USERS; i++){
		//if (t[i] >= threshold) {
			ulib->users[user].vector[i].trust_val = t[i];   //bop_ev(&max_vec[i]);
		//}
		//else
		//{
		//	ulib->users[user].vector[i].trust_val = 0;
		//}
		
	} // Export Opinion expected values's as trust values
	//printf("%f   %f   %f   %d\n",t[user], threshold, user_trust, count);
	return;
}
/*
int tnasl_multiply(Opinion* vec, Opinion** matrix, Opinion* dest){
	int i, j;
	Opinion op_holder;
	for(i=0; i < NUM_USERS; i++){
		for(j=0; j < NUM_USERS; j++){
			if(j == 0)
				op_discount(&vec[0], &matrix[i][0], &dest[i]);
			else{
				op_discount(&vec[j], &matrix[i][j], &op_holder);
				op_consensus(&dest[i],&op_holder, &dest[i]);
			} // Don't consensus first discount; it isn't monotonic
		} // Inner loop of matrix-vector multiplication
	} // Outer loop of matrix-vector multiplication
	
	int max_modified = 0;
	for(i=0; i < NUM_USERS; i++){
		if(op_compare(&dest[i], &max_vec[i]) == 1){
			op_assign(&max_vec[i], &dest[i]);
			max_modified = 1;
		} // Flag flips if a copy to 'max_vec' is made
	} // Update the 'max_value' vector at each position
	return max_modified;
}
*/
// --------------------------- OPINION FUNCTIONS ----------------------------
/*
void op_discount(Opinion* op1, Opinion* op2, Opinion* dest){	
	dest->b = op1->b * op2->b;
	dest->d = op1->b * op2->d;
	dest->u = (1.0 - dest->b - dest->u);
	//dest->u = op1->d + op1->u + (op1->b * op2->u);
	dest->a = op2->a;
	return;
}

void op_consensus(Opinion* op1, Opinion* op2, Opinion* dest){
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
*/
float bop_ev(Opinionb* op){
	//return op->b + (op->a * op->u);
	return op->b;
}

void bop_assign(Opinionb* op1, Opinionb* op2){
	op1->b = op2->b;
	op1->d = op2->d;
	op1->u = op2->u;
	op1->a = op2->a;
	return;
}

int bop_compare(Opinionb* this, Opinionb* that){
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

