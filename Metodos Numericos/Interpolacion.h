#ifndef INTERPOLACION_H_INCLUDED
#define INTERPOLACION_H_INCLUDED
#include "Matriz.h"
#include "EcuacionLineal.h"

/* Devuelve los coeficientes de un polinomio interpolador
Recibe:
   n    - El numero de puntos
   x, y - Las coordenadas de los puntos a interpolar */
double *InterpolarPolinomio(int n, double *x, double *y) {
	double **A = crearMatriz(n, n);
	double **L = crearMatriz(n, n);
	double **U = crearMatriz(n, n);
	int *P     = new int[n];

	for (int i = 0; i < n; i++) {
		A[i][0] = 1;
		for (int j = 1; j < n; j++)
			A[i][j] = x[i] * A[i][j - 1];
	}

	FactorizacionLU(n, A, L, U, P);
	double *coef = ResolverSistema(n, L, U, P, y);

	borrarMatriz(L);
	borrarMatriz(U);
	delete[] P;

	return coef;
}

#endif // INTERPOLACION_H_INCLUDED