#ifndef EIGENPAR_H_INCLUDED
#define EIGENPAR_H_INCLUDED
#include "Matriz.h"
#include "QR.h"
#include <cmath>

//Precision
#ifndef tolerancia 
#define tolerancia 1e-9
#endif

/* Metodo Iterativo de Jacobi para calcular los eigenvalores y eigenvectores de una matriz simetrica.
Recibe: 
   n - Las dimensiones de la matriz
   A - Los datos de la matriz
   M - El numero maximo de iteraciones
Regresa: 
   V - Una matriz con los eigenvectores en las columnas
   D - Una matriz diagonal con los eigenvalores
Devuelve el numero de iteraciones realizadas */
int MetodoJacobi(int n, double **A, int M, double **V, double **D) {
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

		//La matriz es diagonal
		if (fabs(dij) < tolerancia)
			return k;
		
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

	return M;
}

/* Calculo de eigenvalores a traves de la factorizacion QR.
Recibe: 
   n - Las dimensiones de la matriz
   A - Los datos de la matriz
   M - El numero maximo de iteraciones
Regresa: 
   V - Una matriz con los eigenvectores en las columnas (cuando A es simetrica)
   D - Una matriz triangular con los eigenvalores en la diagonal (cuando el algoritmo converge)
Devuelve el numero de iteraciones realizadas */
int MetodoQR(int n, double **A, int M, double **V, double **D) {
	double **Q = crearMatriz(n, n);
	double **R = crearMatriz(n, n);
	matrizIdentidad(n, V);
	copiarMatriz(n, n, A, D);	

	for (int k = 0; k < M; k++) {
		//Mayor elemento fuera de la diagonal
		double dmax = 0;
		for (int r = 0; r < n; r++)
			for (int c = 0; c < r; c++)
				if (fabs(D[r][c]) > dmax)
					dmax = D[r][c];

		//La matriz es diagonal
		if (fabs(dmax) < tolerancia) {
			borrarMatriz(Q);
			borrarMatriz(R);
			return k;
		}

		//No converge
		if (!GramSchmidt(n, n, D, Q, R))
			break;		

		//Actualiza la matriz V
		double **tempV = crearMatriz(n, n);
		copiarMatriz(n, n, V, tempV);
		producto(n, n, n, tempV, Q, V);
		borrarMatriz(tempV);

		//Actualiza la matriz D
		producto(n, n, n, R, Q, D);		
	}

	borrarMatriz(Q);
	borrarMatriz(R);
	return M;
}

#endif // EIGENPAR_H_INCLUDED
