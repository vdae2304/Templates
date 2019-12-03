#ifndef INTERPOLACION_H_INCLUDED
#define INTERPOLACION_H_INCLUDED

#include "Matriz.h"
#include "MatrizFactorizacion.h"
#include "EcuacionLineal.h"

/* Calcula la matriz de Vandermonde
   A = [1   xi   xi^2   ...   xi^(n-1)]   i = 1,...,m
para un conjunto de puntos x.
Recibe: 
   m - El numero de puntos.
   n - El maximo exponente mas 1.
   x - El conjunto de puntos.
Regresa:
   A - La matriz de Vandermonde. */
void MatrizVandermonde(int m, int n, Vector x, Matriz A) {
	for (int i = 0; i < m; i++) {
		A[i][0] = 1;
		for (int j = 1; j < n; j++)
			A[i][j] = x[i] * A[i][j - 1];
	}
}

/* Calcula el polinomio
   c0 + c1*x + c2*x^2 + ... + cn*x^(n-1)
que pasa por un conjunto de puntos dados.
Recibe:
   n    - El numero de puntos.
   x, y - Las coordenadas de los puntos a interpolar.
Devuelve los coeficientes del polinomio interpolador. */
Vector InterpolarPolinomio(int n, Vector x, Vector y) {
	Matriz A = crearMatriz(n, n);
	MatrizVandermonde(n, n, x, A);

	int *P   = new int[n];
	Matriz L = crearMatriz(n, n);
	Matriz U = crearMatriz(n, n);
	FactorizacionLU(n, A, P, L, U);
	borrarMatriz(A);

	Vector c = ResolverEcuacionLU(n, P, L, U, y);
	delete[] P;
	borrarMatriz(L);
	borrarMatriz(U);	

	return c;
}

/* Calcula un polinomio
   c0 + c1*x + c2*x^2 + ... + cn*x^n
que mejor aproxime a un conjunto de puntos dados.
Recibe:
   m    - El numero de puntos.
   n    - El grado del polinomio (n < m).
   x, y - Las coordenadas de los puntos.
Devuelve los coeficientes del polinomio interpolador. */
Vector AjustePolinomial(int m, int n, Vector x, Vector y) {
	Matriz A = crearMatriz(m, ++n);
	MatrizVandermonde(m, n, x, A);

	Matriz AT = crearMatriz(n, m);
	matrizTranspuesta(m, n, A, AT);
	Matriz ATA = crearMatriz(n, n);
	productoMatriz(n, m, n, AT, A, ATA);
	Vector ATy = crearVector(n);
	productoMatrizVector(n, m, AT, y, ATy);

	Matriz L = crearMatriz(n, n);
	FactorizacionCholesky(n, ATA, L);
	borrarMatriz(A);
	borrarMatriz(AT);
	borrarMatriz(ATA);

	Vector c = ResolverEcuacionCholesky(n, L, ATy);
	borrarMatriz(L);
	borrarVector(ATy);

	return c;
}

#endif // INTERPOLACION_H_INCLUDED