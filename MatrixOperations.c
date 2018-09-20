#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MatrixOperations.h"

/*
    Funcao createMatrix: inicializa matriz rowsXcolumns com zeros
    Argumentos: -rows: numero de linhas da matriz
                -columns: numero de colunas da matriz
                -matrix: matriz a ser inicializada
*/

void createMatrix (int rows, int columns, float matrix[rows][columns])
{
    int i = 0, j = 0;

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < columns; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

/*
    Funcao transpose: calcula matriz transposta
    Argumentos: -rows: numero de linhas da matriz
                -columns: numero de colunas da matriz
                -matrix: matriz a ser transposta
                -transpose: matriz transposta
*/

void transpose (int rows, int columns, float matrix[rows][columns], float transpose[columns][rows])
{
    int i = 0, j = 0;

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < columns; j++)
        {
            transpose[j][i] = matrix[i][j];
        }
    }
}

/*
    Funcao add: soma duas matrizes m1 e m2 de mesmo tamanho
    Argumentos: -rows: numero de linhas das matrizes
                -columns: numero de colunas das matrizes
                -m1, m2: matrizes a serem somadas
                -add: matriz resultante da soma
*/

void add (int rows, int columns, float m1[rows][columns], float m2[rows][columns], float add[rows][columns])
{
    int i = 0, j = 0;

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < columns; j++)
        {
            add[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

/*
    Funcao subtract: subtrai duas matrizes m1 e m2 de mesmo tamanho
    Argumentos: -rows: numero de linhas das matrizes
                -columns: numero de colunas das matrizes
                -m1, m2: matrizes a serem subtraidas
                -sub: matriz resultante da subtracao
*/

void subtract (int rows, int columns, float m1[rows][columns], float m2[rows][columns], float sub[rows][columns])
{
    int i = 0, j = 0;

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < columns; j++)
        {
            sub[i][j] = m1[i][j] - m2[i][j];
        }
    }
}

/*
    Funcao multiply: multiplica duas matrizes m1 e m2
    Argumentos: -rows1, columns1: numero de linhas e colunas, respectivamente, da matriz m1
                -rows2, columns2: numero de linhas e colunas, respectivamente, da matriz m2
                -m1, m2: matrizes a serem multiplicadas
                -mult: matriz resultante da multiplicacao
*/

void multiply (int rows1, int columns1, int rows2, int columns2, float m1[rows1][columns1], float m2[rows2][columns2], float mult[rows1][columns2])
{
    int i = 0, j = 0, k = 0;

    createMatrix (rows1, columns2, mult);

	for(i = 0; i < rows1; i++)
    {
        for(j = 0; j < columns2; j++)
        {
            for(k = 0; k < columns1; k++)
            {
                    mult[i][j] += m1[i][k] * m2[k][j];
            }
        }
	}
}

/*
    Funcao determinant: calcula o determinante de uma matriz (utilizado na funcao inverse)
    Argumentos: -rows: numero de linhas da matriz
                -columns: numero de colunas da matriz
                -a: matriz que sera calculada o determinante
                -k: flag
*/

float determinant (int rows, int columns, float a[rows][columns], int k)
{
    float s = 1, det = 0, b[rows][columns];
    int i = 0, j = 0, m = 0, n = 0, c = 0;

    if (k == 1)
    {
        return (a[0][0]);
    }

    else
    {
        det=0;
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < k; i++)
            {
                for (j = 0; j < k; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        b[m][n] = a[i][j];
                        if (n < (k-2))
                        {
                            n++;
                        }
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(rows, columns, b, k-1));
            s = -1 * s;
        }
    }
    return (det);
}


/*
    Funcao inverse: calcula a inversa de uma matriz quadrada
    Argumentos: -rows: numero de linhas da matriz
                -columns: numero de colunas da matriz
                -num: matriz que sera calculada a inversa
                -inverse: inversa de num
                -k: flag
*/

void inverse (int rows, int columns, float num[rows][columns], float inverse[rows][columns], int k)
{
    float b[rows][columns], fac[rows][columns], d;
    int p = 0, q = 0, m = 0, n = 0, i = 0, j = 0;

    if (k == 1)
    {
        if(num[0][0] != 0)
        {
            inverse[0][0] = 1/num[0][0];
            return;
        }
    }

    for (q = 0; q < k; q++)
    {
        for (p = 0; p < k; p++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < k; i++)
            {
                for (j = 0; j < k; j++)
                {
                    if (i != q && j != p)
                    {
                        b[m][n] = num[i][j];
                        if (n < (k-2))
                        {
                            n++;
                        }
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1,q + p) * determinant(rows, columns, b, k-1);
        }
    }

    d = determinant(rows, columns, num, k);
    transpose(k, k, fac, b);

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < k; j++)
        {
            inverse[i][j] = b[i][j] / d;
        }
    }
}

/*
    Funcao generateNormal: Gera o vetor normal do plano.
*/

float generateNormal(float mean, float variance)
{
    float x1 = 0, x2 = 0;
    x1 = (rand()+1.0)/(RAND_MAX+1.0);
    x2 = (rand()+1.0)/(RAND_MAX+1.0);

    return (mean + variance * sqrt(-2*log(x1)) * cos(2*M_PI*x2));
}

/*
    Funcao eye: cria uma matriz identidade rowsXcolumns (Matriz identidade: contem 1's na diagonal principal e zeros nos restantes)
    Argumentos: -rows: numero de linhas da matriz
                -columns: numero de colunas da matriz
                -matrix: matriz identidade rowsXcolumns
*/

void eye (int rows, int columns, float matrix[rows][columns])
{
    int i = 0, j = 0;

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < columns; j++)
        {
            if(i == j)
            {
                matrix[i][j] = 1;
            }

            else
            {
                matrix[i][j] = 0;
            }
        }
    }
}

/*
    Funcao multScalar: realiza a multiplicacao de uma matriz por um escalar
    Argumentos: -rows: numero de linhas da matriz
                -columns: numero de colunas da matriz
                -matrix: matriz a ser multiplicada
                -s: escalar
*/

void multScalar (int rows, int columns, float matrix[rows][columns], float s)
{
    int i = 0, j = 0;

    for(i = 0; i < rows; i ++)
    {
        for(j = 0; j < columns; j++)
        {
            matrix[i][j] = matrix[i][j] * s;
        }
    }
}

/*
    Funcao hfunc:
*/

float hfunc (int rows, int columns, float xhat[rows][columns])
{
    float x1 = xhat[0][0];
    float x3 = xhat[2][0];
    float res = sqrt(x1*x1 + x3*x3);

    return (res);
}

/*
    Funcao Hjacob: calcula a jacobiana de uma matriz
    Argumentos: -rows: numero de linhas da matriz
                -columns: numero de colunas da matriz
                -x: matriz base rowsXcolumns
                -H: jacobiana columnsXrows
*/

void Hjacob (int rows, int columns, float x[rows][columns], float H[columns][rows])
{
    float x1 = x[0][0];
    float x3 = x[2][0];

    H[0][0] = x1 / sqrt(x1*x1 + x3*x3);
    H[0][1] = 0;
    H[0][2] = x3 / sqrt(x1*x1 + x3*x3);
}
