#ifndef ECUACIONLINEAL_H_INCLUDED
#define ECUACIONLINEAL_H_INCLUDED
#include "Matriz.h"
#include <cmath>
#include <algorithm>

//Precision
#define epsilon 1e-9

/* Resuelve la ecuacion lineal Lx = b, donde L es una matriz triangular inferior
Recibe:
   n - Las dimensiones de la matriz
   L - Los datos de la matriz
   b - El vector de terminos independientes
Si la solucion existe, devuelve un vector con la solucion
De lo contrario, devuelve NULL */
double *SustitucionHaciaAdelante(int n, double **L, double *b) {	
	double *x = new double[n];
	for (int i = 0; i < n; i++) {
		if (fabs(L[i][i]) < epsilon) {
			delete[] x;
			return NULL;
		}
		
		x[i] = b[i];
		for (int j = 0; j < i; j++) 
			x[i] -= L[i][j] * x[j];
		x[i] /= L[i][i];
	}
	return x;
}

/* Resuelve la ecuacion lineal Ux = b, donde U es una matriz triangular superior
Recibe:
   n - Las dimensiones de la matriz
   U - Los datos de la matriz
   b - El vector de terminos independientes
Si la solucion existe, devuelve un vector con la solucion
De lo contrario, devuelve NULL */
double *SustitucionHaciaAtras(int n, double **U, double *b) {
	double *x = new double[n];
	for (int i = n - 1; i >= 0; i--) {
		if (fabs(U[i][i]) < epsilon) {
			delete[] x;
			return NULL;
		}
		
		x[i] = b[i];
		for (int j = i + 1; j < n; j++)
			x[i] -= U[i][j] * x[j];
		x[i] /= U[i][i];
	}
	return x;
}

/* Calcula la factorizacion LU de una matriz cuadrada
Recibe:
   n - Las dimensiones de la matriz
   A - Los datos de la matriz
Regresa:   
   L - Los datos la matriz inferior L
   U - Los datos la matriz superior U
   P - El vector de permutacion
Si la factorizacion existe, devuelve true
En caso contrario, devuelve false */
bool FactorizacionLU(int n, double **A, double **L, double **U, int *P) {
	matrizIdentidad(n, L);
	copiarMatriz(n, A, U);
	for (int i = 0; i < n; i++) 
		P[i] = i;
	
	for (int k = 0; k < n; k++) {
		//Pivoteo
		int r = k;
		for (int i = k + 1; i < n; i++)
			if (fabs(U[i][k]) > fabs(U[r][k]))
				r = i;
		
		//No existe la factorizacion
		if (fabs(U[r][k]) < epsilon)
			return false;
		
		//Intercambio de renglones
		if (r != k) {
			for (int j = 0; j < k; j++)
				swap(L[k][j], L[r][j]);
			for (int j = k; j < n; j++)
				swap(U[k][j], U[r][j]);
			swap(P[k], P[r]);
		}
		
		//Eliminacion gaussiana
		for (int i = k + 1; i < n; i++) {
			L[i][k] = U[i][k] / U[k][k];
			U[i][k] = 0;
			for (int j = k + 1; j < n; j++)
				U[i][j] -= L[i][k] * U[k][j];			
		}	
	}

	return true;
}

/* Resuelve el sistema Ax = b dada su factorizacion LU
Recibe:
   n - Las dimensiones de la matriz
   L - La matriz inferior
   U - La matriz superior
   P - El vector de permutacion
   b - El vector de terminos independientes
Devuelve un vector con la solucion del sistema PLUx = b*/
double *ResolverSistema(int n, double **L, double **U, int *P, double *b) {
	double *Pb = new double[n];
	for (int i = 0; i < n; i++)
		Pb[i] = b[P[i]];
	
	double *y = SustitucionHaciaAdelante(n, L, Pb);
	delete[] Pb;
	double *x = SustitucionHaciaAtras(n, U, y);
	delete[] y;
	
	return x;
}

#endif // ECUACIONLINEAL_H_INCLUDED
