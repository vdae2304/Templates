#ifndef INTERPOLACION_H_INCLUDED
#define INTERPOLACION_H_INCLUDED

#include "Matriz.h"
#include "MatrizFactorizacion.h"
#include "EcuacionLineal.h"

/* Calcula la matriz de Vandermonde
   A = [1   xi   xi^2   ...   xi^(n-1)]   i = 0, ..., m-1
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

/* Calcula el polinomio
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

/* Construye un spline natural cubico 
  S_i(x) = c_i0*(x_(i+1) - x)^3 + c_i1*(x - x_i)^3 + c_i2*(x - x_i) + c_i3,   x_i <= x <= x_(i+1),   i = 0,...,n-2
que pase por un conjunto de puntos dado
Recibe:
   n    - El numero de puntos.
   x, y - Las coordenadas de los puntos, ordenados por su coordenada en x.
Devuelve una matriz en donde cada renglon contiene los coeficientes del spline en el intervalo 
correspondiente. */
Matriz SplineCubico(int n, Vector x, Vector y) {
	Vector h = crearVector(n - 1);
	for (int i = 0; i < n - 1; i++)
		h[i] = x[i + 1] - x[i];

	//Sistema de ecuaciones
	Matriz A = crearMatriz(3, n);
	Vector b = crearVector(n);
	matrizCero(3, n, A);
	vectorCero(n, b);

	A[1][0] = A[1][n - 1] = 1;
	for (int i = 1; i < n - 2; i++) {
		A[0][i] = h[i] / (h[i] + h[i + 1]);
		A[2][i] = h[i] / (h[i - 1] + h[i]);
	}
	for (int i =  1; i < n - 1; i++) {
		A[1][i] = 2;
		b[i]    = 6/(h[i - 1] + h[i]) * ((y[i + 1] - y[i])/h[i] - (y[i] - y[i - 1])/h[i - 1]);
	}

	Vector M = ResolverEcuacionTridiagonal(n, A, b);
	borrarMatriz(A);
	borrarVector(b);

	//Coeficientes del spline
	Matriz  c = crearMatriz(n - 1, 4);
	for (int i = 0; i < n - 1; i++) {
		c[i][0] = M[i]/(6*h[i]);
		c[i][1] = M[i + 1]/(6*h[i]);
		c[i][2] = (y[i + 1] - y[i])/h[i] - (M[i + 1] - M[i])*h[i]/6;
		c[i][3] = y[i] - M[i]*h[i]*h[i]/6;
	}

	borrarVector(M);
	borrarVector(h);
	return c;
}

#endif // INTERPOLACION_H_INCLUDED