#ifndef QR_H_INCLUDED
#define QR_H_INCLUDED

#include "Matriz.h"
#include <cmath>
#include <algorithm>

//Precision
#ifndef tolerancia 
#define tolerancia 1e-9
#endif

/* Calcula la factorizacion PA = LU donde A es una matriz cuadrada, P es una matriz de permutacion, 
L es una matriz triangular inferior y U es una matriz triangular superior.
Recibe:
   n - Las dimensiones de la matriz.
   A - Los datos de la matriz.
Regresa:
   P - El vector de permutacion.
   L - Los datos la matriz inferior.
   U - Los datos la matriz superior.
Si la factorizacion existe, devuelve true. En caso contrario, devuelve false */
bool FactorizacionLU(int n, Matriz A, int *P, Matriz L, Matriz U) {
	matrizIdentidad(n, L);
	copiarMatriz(n, n, A, U);
	for (int i = 0; i < n; i++) 
		P[i] = i;
	
	for (int k = 0; k < n; k++) {
		//Pivoteo
		int r = k;
		for (int i = k + 1; i < n; i++)
			if (fabs(U[i][k]) > fabs(U[r][k]))
				r = i;
		
		//No existe la factorizacion
		if (fabs(U[r][k]) < tolerancia)
			return false;
		
		//Intercambio de renglones
		if (r != k) {
			for (int j = 0; j < k; j++)
				std::swap(L[k][j], L[r][j]);
			for (int j = k; j < n; j++)
				std::swap(U[k][j], U[r][j]);
			std::swap(P[k], P[r]);
		}
		
		//Eliminacion gaussiana
		for (int i = k + 1; i < n; i++) {
			L[i][k] = U[i][k] / U[k][k];
			for (int j = k; j < n; j++)
				U[i][j] -= L[i][k] * U[k][j];
		}
	}

	return true;
}

/* Calcula la factorizacion de Cholesky A = LL^T donde A es una matriz simetrica positiva definida
y L es una matriz triangular inferior.
Recibe:
   n - Las dimensiones de la matriz.
   A - Los datos de la matriz.
Regresa:
   L - Los datos la matriz inferior.
Si la factorizacion existe, devuelve true. En caso contrario, devuelve false */
bool FactorizacionCholesky(int n, Matriz A, Matriz L) {
	for (int j = 0; j < n; j++) {
		L[j][j] = A[j][j];
		for (int k = 0; k < j; k++)
			L[j][j] -= L[j][k] * L[j][k];

		//No existe la factorizacion
		if (L[j][j] < 0) 
			return false;
		L[j][j] = sqrt(L[j][j]);

		//No existe la factorizacion
		if (L[j][j] < tolerancia)
			return false;

		for (int i = j + 1; i < n; i++) {
			L[i][j] = A[i][j];
			for (int k = 0; k < j; k++)
				L[i][j] -= L[i][k] * L[j][k];
			L[i][j] /= L[j][j];
		}
	}
	
	return true;
}

/* Proceso de Ortogonalizacion de Gram-Schmidt para calcular la factorizacion A = QR de una matriz.
Recibe: 
   n, m - Las dimensiones de la matriz   
   A    - Los datos de la matriz
Regresa: 
   Q - Una matriz ortonormal
   R - Una matriz triangular superior
Devuelve true si la factorizacion existe y false en caso contrario*/
bool GramSchmidt(int n, int m, Matriz A, Matriz Q, Matriz R) {
	copiarMatriz(n, m, A, Q);
	matrizCero(m, m, R);

	for (int i = 0; i < m; i++) {
		//Norma de la i-esima columna
		for (int k = 0; k < n; k++)
			R[i][i] += Q[k][i] * Q[k][i];
		R[i][i] = sqrt(R[i][i]);
		
		//No existe la factorizacion
		if (fabs(R[i][i]) < tolerancia)
			return false;

		//Actualiza Q y R
		for (int k = 0; k < n; k++)
			Q[k][i] /= R[i][i];

		for (int j = i + 1; j < m; j++) {
			for (int k = 0; k < n; k++)
				R[i][j] += Q[k][i] * Q[k][j];
			for (int k = 0; k < n; k++)
				Q[k][j] -= R[i][j] * Q[k][i];
		}
	}

	return true;
}

#endif // QR_H_INCLUDED