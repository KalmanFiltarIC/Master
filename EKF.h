#ifndef EKF_H
#define EKF_H

#include <stdio.h>
#include <stdlib.h>

#include "MatrixOperations.h"

/*
    EKF: Contem as funcoes RadarEKF e GetRadar
*/

void RadarEKF (int rows1, int columns1, int rows2, int columns2, float A[rows1][columns1], float P[rows1][columns1], float R[rows2][columns2], float Q[rows1][columns1], float x[rows1][columns1], float z[rows2][columns2], int *firstrun, float dt);

float GetRadar(float dt, float *posp, float *pos, float *vel, float *alt, int i);

#endif /* EKF_H */

