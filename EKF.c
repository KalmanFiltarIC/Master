#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MatrixOperations.h"
#include "EKF.h"

/*
    OBS: rows1 = 3, columns1 = 3, rows2 = 1, columns2 = 1
*/

/*
    Funcao RadarEKF: funcao principal. Calcula a matriz x (state variable) que contem os dados de pos, vel e alt.
    Argumentos: -rows1, rows2: numero de linhas das diferentes matrizes
                -columns1, columns2: numero de colunas das diferentes matrizes
                -A, P, R, Q: system model
                -x: state variable (estimate)
                -z: measurement (matriz calculada a partir da funcao GetRadar)
                -firstrun: flag para indicar se e' a primeira vez que roda o codigo
                -dt: constante
*/

void RadarEKF (int rows1, int columns1, int rows2, int columns2, float A[rows1][columns1], float P[rows1][columns1], float R[rows2][columns2], float Q[rows1][columns1], float x[rows1][columns2], float z[rows2][columns2], int *firstrun, float dt)
{
    if(*firstrun != 1)
    {
        float mA1[rows1][columns1];
        float mA2[rows1][columns1];

        //Calculo da matriz A
        eye(rows1, columns1, mA1);

        createMatrix(rows1, columns1, mA2);
        mA2[0][1] = 1;
        multScalar(rows1, columns1, mA2, dt);

        add(rows1, columns1, mA1, mA2, A);

        //Calculo da matriz Q
        createMatrix(rows1, columns1, Q);
        Q[1][1] = 0.001;
        Q[2][2] = 0.001;

        //Calculo da matriz R
        R[0][0] = 10;

        //Calculo da matriz x
        x[0][0] = 0;
        x[1][0] = 90;
        x[2][0] = 1100;

        //Calculo da matriz P
        eye(rows1, columns1, P);
        multScalar(rows1, columns1, P, 10);

        //
        *firstrun = 1;
    }

    float H[rows2][columns1];
    float Ht[rows1][columns2];
    float At[rows1][columns1];

    float xp[rows1][columns2];
    float Pp[rows1][columns1];

    //Ganho de Kalman K
    float K[rows1][columns2];

    //Matrizes Auxiliares
    float aux[rows1][columns1]; //3x3
    float aux2[rows2][columns1]; //1x3
    float aux3[rows2][columns2]; //1x1
    float aux4[rows1][columns2]; //3x1

    // H = Hjacob(x)
    Hjacob(rows1, columns2, x, H);

    // Ht = H'
    transpose(rows2, columns1, H, Ht);

    // Xp = A*x
    multiply(rows1, columns1, rows1, columns2, A, x, xp);

    //At = A'
    transpose(rows1, columns1, A, At);

    // Pp = A*P*A' + Q
    multiply(rows1, columns1, rows1, columns1, A, P, aux);
    multiply(rows1, columns1, rows1, columns1, aux, At, Pp);
    add(rows1, columns1, Pp, Q, Pp);

    // K = Pp*H'*inv(H*Pp*H' + R)
    multiply(rows1, columns1, rows1, columns2, Pp, Ht, aux4); //Pp*H' = aux4

    multiply(rows2, columns1, rows1, columns1, H, Pp, aux2); //H*Pp = aux2
    multiply(rows2, columns1, rows1, columns2, aux2, Ht, aux3); // aux2*H' = aux3
    add(rows2, columns2, aux3, R, aux3); //aux3 + R = aux3
    inverse(rows2, columns2, aux3, aux3, 1); //inv(H*Pp*H' + R) = aux3

    multiply(rows1, columns2, rows2, columns2, aux4, aux3, K); //K = Pp*H'*inv(H*Pp*H' + R) = aux4*aux3

    // x = xp + K*(z-hx(xp))
    aux3[0][0] = hfunc(rows1, columns2, xp); //hx(xp)
    subtract(rows2, columns2, z, aux3, aux3); //z-hx(xp) = aux3
    multiply(rows1, columns2, rows2, columns2, K, aux3, aux4); //K*(z-hx(xp)) = aux4
    add(rows1, columns2, xp, aux2, x); //x = xp + K*(z-hx(xp)) = xp + aux4

    // P = Pp - K*H*Pp
    multiply(rows1, columns2, rows2, columns1, K, H, aux); //K*H = aux
    multiply(rows1, columns1, rows1, columns1, aux, Pp, aux); // K*H*Pp = aux
    subtract(rows1, columns1, Pp, aux, P); // P = Pp - K*H*Pp = Pp-aux
}

/*
    Funcao GetRadar: funcao utilizada para calcular o measurement z (r dentro da funcao)
    Argumentos: -dt: constante
                -posp: flag
                -pos, vel, alt: dados utilizados para calculo de r
                -i: flag
*/

float GetRadar(float dt, float *posp, float *pos, float *vel, float *alt, int i)
{
    float r = 0;
    float createnumber;
    float randn;
	float v = 0;
	int p = 0;

	p = *posp;

    createnumber = rand() % 10000;
    randn = createnumber/10000;

	vel[i] = 100 + 5*randn;
	alt[i] = 1000 + 10*randn;
	pos[i] = p + vel[i]*dt;

	v = 0 + pos[i]*dt*randn;

	r = sqrt(pos[i]*pos[i] + alt[i]*alt[i]) + v;

	*posp = pos[i];

	return r;
}

