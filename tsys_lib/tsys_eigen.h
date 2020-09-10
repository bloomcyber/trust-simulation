                                        
// Andrew West - tsys_eigen.h - Header file for tsys_eigen.c

#ifndef TSYS_EIGEN_H
#define TSYS_EIGEN_H

// -------------------------- LOCAL INCLUDES --------------------------------


// ------------------------ STRUCTS & DATATPYPES ----------------------------


// ------------------------ FUNCTION PROTOTYPES -----------------------------

void eigen_compute_trust(Network* nw, int user, int cycle);
void eigen_update(Network* nw, int new_vec, int new_row);

void eigen_initialize(User_Library* ulib);
void eigen_normalize_vector(User_Library* ulib, int new_vec);
float* eigen_trust_multiply(User_Library* ulib, int user, int max_iters);
void eigen_single_multiply(float* source_vec, float* dest_vec);

int eigen_converged(float* vec1, float* vec2);
int eigen_fback_int(Relation* rel);

void lalg_vector_matrix_mult(float* vector, float** matrix, float* dest_vec);
void lalg_constant_vector_mult(float constant, float* vector, float* dest_vec);
void lalg_vector_add(float* vector1, float* vector2, float* dest_vec);

#endif

