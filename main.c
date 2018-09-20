#include <stdio.h>
#include <stdlib.h>

#include "MatrixOperations.h"
#include "EKF.h"

#define N_MAX 3
#define N_MIN 1

/*
A[3X3], Q[3X3], R[1X1], x[3X1], P[3X3], H[1X3], Ht[3X1], z[1X1], Xp[3X1], Pp[3X3], K[3X1]
*/

/*
    Funcao printResults: imprime o numero de testes realizados e os resultados obtidos correspondentes armazenados em PosSaved, VelSaved e AltSaved
    Argumentos: -pos: vetor PosSaved
                -vel: vetor VelSaved
                -alt: vetor AltSaved
                -Nsamples: numero de testes
*/

void printResults (float *pos, float *vel, float *alt, int Nsamples)
{
    int i = 0;
    printf("Numero de Testes: %d\n\n\t\tPos\t\t\tVel\t\t\tAlt\n", Nsamples);
    for(i = 0; i < Nsamples; i++)
    {
        printf("test[%d]:\t%f\t\t%f\t\t%f\n", i+1, pos[i], vel[i], alt[i]);
    }
}

int main()
{
    int firstrun = 0, i = 0, Nsamples = 0;
    float dt = 0.05, posp = 0;

    //Inicializa Matrizes e vetores
    float A[N_MAX][N_MAX], P[N_MAX][N_MAX], R[N_MIN][N_MIN], Q[N_MAX][N_MAX], x[N_MAX][N_MIN], z[N_MIN][N_MIN], r[N_MIN][N_MIN];

    createMatrix(N_MAX, N_MAX, A);
    createMatrix(N_MAX, N_MAX, P);
    createMatrix(N_MIN, N_MIN, R);
    createMatrix(N_MAX, N_MAX, Q);
    createMatrix(N_MAX, N_MIN, x);
    createMatrix(N_MIN, N_MIN, z);
    createMatrix(N_MIN, N_MIN, r);

    //Numero de testes
	Nsamples = 400;

	float t[Nsamples], pos[Nsamples] = {0}, vel[Nsamples] = {0}, alt[Nsamples] = {0};
    float PosSaved[Nsamples] = {0}, VelSaved[Nsamples] = {0}, AltSaved[Nsamples] = {0};

	/*for(i = 0; i < Nsamples; i++)
	{
		t[i] = rand() %20 + 1;
	}*/


	float Xsaved[Nsamples][N_MAX];
	float Zsaved[Nsamples][N_MIN];

	createMatrix(Nsamples, N_MAX, Xsaved);
    createMatrix(Nsamples, N_MIN, Zsaved);

    //Realizacao dos Testes
	for(i = 0; i < Nsamples; i++)
	{
		r[0][0] = GetRadar(dt, &posp, pos, vel, alt, i);
		Zsaved[i][0] = r[0][0];
		RadarEKF(N_MAX, N_MAX, N_MIN, N_MIN, A, P, R, Q, x, r, &firstrun, dt);

        Xsaved[i][0] = x[0][0]; //pos
        Xsaved[i][1] = x[1][0]; //vel
        Xsaved[i][2] = x[2][0]; //alt
	}

	for(i = 0; i < Nsamples; i++)
    {
        PosSaved[i] = Xsaved[i][0];
        VelSaved[i] = Xsaved[i][1];
        AltSaved[i] = Xsaved[i][2];
    }

    //Imprime os resultados
    printResults(PosSaved, VelSaved, AltSaved, Nsamples);

	return 0;
}
