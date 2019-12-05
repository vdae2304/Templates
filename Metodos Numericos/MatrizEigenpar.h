#ifndef MATRIZEIGENPAR_H_INCLUDED
#define MATRIZEIGENPAR_H_INCLUDED

#include "Matriz.h"
#include "MatrizFactorizacion.h"
#include <cmath>

//Precision
#ifndef tolerancia 
#define tolerancia 1e-9
#endif

/* Calcula mediante el Metodo Iterativo de Jacobi la descomposicion espectral A = VDV^T donde A es 
una matriz simetrica, V es una matriz ortonormal cuyas columnas son los eigenvectores de A y D es 
una matriz diagonal cuyos elementos en la diagonal son los eigenvalores de A.
Recibe: 
   n - Las dimensiones de la matriz.
   A - Los datos de la matriz.
   M - El numero maximo de iteraciones.
Regresa: 
   V - Los datos de la matriz ortonormal.
   D - Los datos de la matriz diagonal.
Devuelve el numero de iteraciones realizadas. */
int MetodoJacobi(int n, Matriz A, int M, Matriz V, Matriz D) {
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

/* Calcula mediante la factorizacion QR, la factorizacion de Schur A = VUV^T donde A es una matriz 
cuadrada, V es una matriz ortonormal y U es una matriz triangular superior cuyos elementos en la 
diagonal son los eigenvalores de A.
Comentarios: El algoritmo puede no converger. Si la matriz es simetrica, la factorizacion de Schur
coincide con la descomposicion espectral.
Recibe: 
   n - Las dimensiones de la matriz.
   A - Los datos de la matriz.
   M - El numero maximo de iteraciones.
Regresa: 
   V - Los datos de la matriz ortonormal.
   U - Los datos de la matriz triangular superior.
Devuelve el numero de iteraciones realizadas. */
int MetodoQR(int n, Matriz A, int M, Matriz V, Matriz U) {
	Matriz Q     = crearMatriz(n, n);
	Matriz R     = crearMatriz(n, n);
	Matriz tempV = crearMatriz(n, n)
	matrizIdentidad(n, V);
	copiarMatriz(n, n, A, U);

	for (int k = 0; k < M; k++) {
		//Mayor elemento debajo de la diagonal
		double umax = 0;
		for (int r = 0; r < n; r++)
			for (int c = 0; c < r; c++)
				if (fabs(D[r][c]) > umax)
					umax = D[r][c];

		//La matriz es diagonal
		if (fabs(umax) < tolerancia) {
			borrarMatriz(Q);
			borrarMatriz(R);
			borrarMatriz(tempV);
			return k;
		}

		//No converge
		if (!GramSchmidt(n, n, U, Q, R))
			break;		

		//Actualiza las matrices V y U
		copiarMatriz(n, n, V, tempV);
		producto(n, n, n, tempV, Q, V);
		producto(n, n, n, R, Q, U);
	}

	borrarMatriz(Q);
	borrarMatriz(R);
	borrarMatriz(tempV);
	return M;
}

#endif // MATRIZEIGENPAR_H_INCLUDED