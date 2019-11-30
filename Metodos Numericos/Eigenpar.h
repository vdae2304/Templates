#ifndef EIGENPAR_H_INCLUDED
#define EIGENPAR_H_INCLUDED
#include "Matriz.h"
#include <cmath>

//Precision
#ifndef epsilon 
#define epsilon 1e-9
#endif

/*
3
100
1 2 3
2 5 6
3 6 9
*/

/* Metodo iterativo de Jacobi para calcular los eigenvalores y eigenvectores de una matriz simetrica.
Recibe: 
   n - Las dimensiones de la matriz
   A - Los datos de la matriz
   M - El numero maximo de iteraciones
Regresa: 
   V - La matriz con los eigenvectores en las columnas
   D - La matriz con los eigenvalores en la diagonal */
void MetodoJacobi(int n, double **A, int M, double **V, double **D) {
	matrizIdentidad(n, V);
	copiarMatriz(n, n, A, D);

	for (int k = 0; k < M; k++) {
		//Mayor elemento fuera de la diagonal
		int i = 1, j = 0;
		for (int r = 0; r < n; r++)
			for (int c = 0; c < r; c++)
				if (fabs(D[r][c]) > fabs(D[i][j])) {
					i = r;
					j = c;
				}
				
		double dii = D[i][i];
		double djj = D[j][j];
		double dij = D[i][j];

		//La matriz ya es diagonal
		if (fabs(dij) < epsilon)
			break;
		
		//Rotacion de Givens
		double delta = (djj - dii) / (2*dij);
		double t = (delta > 0 ? 1 : -1) / (fabs(delta) + sqrt(1 + delta*delta));
		double c = 1/sqrt(1 + t*t);
		double s = c*t;		

		//Actualiza la matriz V
		for (int l = 0; l < n; l++) {
			double vli = V[l][i];
			double vlj = V[l][j];
			V[l][i] = c*vli - s*vlj;
			V[l][j] = s*vli + c*vlj;
		}

		//Actualiza la matriz D
		D[i][i] = c*c*dii - 2*s*c*dij + s*s*djj;
		D[j][j] = s*s*dii + 2*s*c*dij + c*c*djj;
		D[i][j] = D[j][i] = 0;

		for (int l = 0; l < n; l++)
			if (l != i && l != j) {
				double dli = D[l][i];
				double dlj = D[l][j];
				D[i][l] = D[l][i] = c*dli - s*dlj;
				D[j][l] = D[l][j] = s*dli + c*dlj;
			}
	}
}

#endif // EIGENPAR_H_INCLUDED
