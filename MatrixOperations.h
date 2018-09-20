#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

#include <stdio.h>
#include <stdlib.h>

/*
    MatrixOperations: Contem todas as operacoes utilizadas que envolvem matrizes.
*/

void createMatrix (int rows, int columns, float matrix[rows][columns]);
void transpose (int rows, int columns, float matrix[rows][columns], float transpose[rows][columns]);
void add (int rows, int columns, float m1[rows][columns], float m2[rows][columns], float add[rows][columns]);
void subtract (int rows, int columns, float m1[rows][columns], float m2[rows][columns], float sub[rows][columns]);
void multiply (int rows1, int columns1, int rows2, int columns2, float m1[rows1][columns1], float m2[rows1][columns2], float mult[rows1][columns2]);
float determinant (int rows, int columns, float a[rows][columns], int k);
void inverse (int rows, int columns, float num[rows][columns], float inverse[rows][columns], int k);
float generateNormal (float mean, float variance);
void eye (int rows, int columns, float matrix[rows][columns]);
void multScalar (int rows, int columns, float matrix[rows][columns], float s);
float hfunc (int rows, int columns, float xhat[rows][columns]);
void Hjacob (int rows, int columns, float x[rows][columns], float H[rows][columns]);

#endif /* MATRIXOPERATIONS_H */

