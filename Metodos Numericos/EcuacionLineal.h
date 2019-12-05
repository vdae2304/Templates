#ifndef ECUACIONLINEAL_H_INCLUDED
#define ECUACIONLINEAL_H_INCLUDED

#include "Matriz.h"
#include <cmath>

//Precision
#ifndef tolerancia 
#define tolerancia 1e-9
#endif

/* Resuelve la ecuacion lineal Lx = b, donde L es una matriz triangular inferior.
Recibe:
   n - Las dimensiones de la matriz.
   L - Los datos de la matriz.
   b - El vector de terminos independientes.
Si la solucion existe, devuelve un vector con la solucion, de lo contrario devuelve NULL. */
Vector SustitucionHaciaAdelante(int n, Matriz L, Vector b) {	
	Vector x = crearVector(n);
	for (int i = 0; i < n; i++) {
		if (fabs(L[i][i]) < tolerancia) {
			borrarVector(x);
			return NULL;
		}
		
		x[i] = b[i];
		for (int j = 0; j < i; j++) 
			x[i] -= L[i][j] * x[j];
		x[i] /= L[i][i];
	}
	return x;
}

/* Resuelve la ecuacion lineal Ux = b, donde U es una matriz triangular superior.
Recibe:
   n - Las dimensiones de la matriz.
   U - Los datos de la matriz.
   b - El vector de terminos independientes.
Si la solucion existe, devuelve un vector con la solucion, de lo contrario devuelve NULL */
Vector SustitucionHaciaAtras(int n, Matriz U, Vector b) {
	Vector x = crearVector(n);
	for (int i = n - 1; i >= 0; i--) {
		if (fabs(U[i][i]) < tolerancia) {
			borrarVector(x);
			return NULL;
		}
		
		x[i] = b[i];
		for (int j = i + 1; j < n; j++)
			x[i] -= U[i][j] * x[j];
		x[i] /= U[i][i];
	}
	return x;
}

/* Resuelve la ecuacion lineal Ax = b dada su factorizacion PA = LU.
Recibe:
   n - Las dimensiones de la matriz.
   P - El vector de permutacion.
   L - La matriz triangular inferior.
   U - La matriz triangular superior.
   b - El vector de terminos independientes.
Devuelve un vector con la solucion del sistema. */
Vector ResolverEcuacionLU(int n, int *P, Matriz L, Matriz U, Vector b) {
	Vector Pb = crearVector(n);
	for (int i = 0; i < n; i++)
		Pb[i] = b[P[i]];
	
	Vector y = SustitucionHaciaAdelante(n, L, Pb);
	borrarVector(Pb);
	Vector x = SustitucionHaciaAtras(n, U, y);
	borrarVector(y);
	
	return x;
}

/* Resuelve la ecuacion lineal Ax = b dada su factorizacion de Cholesky A = LL^T.
Recibe:
   n - Las dimensiones de la matriz.
   L - La matriz triangular inferior.
   b - El vector de terminos independientes.
Devuelve un vector con la solucion del sistema. */
Vector ResolverEcuacionCholesky(int n, Matriz L, Vector b) {
	Matriz U = crearMatriz(n, n);
	matrizTranspuesta(n, n, L, U);
	
	Vector y = SustitucionHaciaAdelante(n, L, b);
	Vector x = SustitucionHaciaAtras(n, U, y);
	borrarMatriz(U);
	borrarVector(y);
	
	return x;
}

/* Resuelve la ecuacion lineal Ax = b dada su factorizacion A = QR.
Recibe:
   n - Las dimensiones de la matriz.
   Q - La matriz ortonormal.
   R - La matriz triangular superior
   b - El vector de terminos independientes.
Devuelve un vector con la solucion del sistema. */
Vector ResolverEcuacionQR(int n, Matriz Q, Matriz R, Vector b) {
	Matriz QT  = crearMatriz(n, n);
	Vector QTb = crearVector(n);
	matrizTranspuesta(n, n, Q, QT);
	productoMatrizVector(n, n, QT, b, QTb);
	
	Vector x = SustitucionHaciaAtras(n, R, QTb);
	borrarMatriz(QT);
	borrarVector(QTb);
	
	return x;
}

/* Resuelve la ecuacion lineal Ax = b donde A es una matriz tridiagonal.
Recibe:
   n - Las dimensiones de la matriz.
   A - Los datos de la matriz ordenados de la siguiente manera:
       En el primer renglon los elementos de la subdiagonal.
       En el segundo renglon los elementos de la diagonal.
       En el tercer renglon los elementos de la supdiagonal.
   b - El vector de terminos independientes.
Devuelve un vector con la solucion del sistema o NULL si no existe. */
Vector ResolverEcuacionTridiagonal(int n, Matriz A, Vector b) {
	if (fabs(A[1][0]) < tolerancia)
		return NULL;
	Matriz Atemp = crearMatriz(3, n);
	Vector x     = crearVector(n);

	Atemp[0][0] = b[0];
	Atemp[1][0] = A[1][0];
	Atemp[2][0] = A[2][0];
	for  (int i = 1; i < n; i++) {
		Atemp[0][i] = Atemp[1][i - 1]*b[i]    - A[0][i - 1]*Atemp[0][i - 1];
		Atemp[1][i] = Atemp[1][i - 1]*A[1][i] - A[0][i - 1]*Atemp[2][i - 1];
		Atemp[2][i] = Atemp[1][i - 1]*A[2][i];

		if (fabs(Atemp[1][i]) < tolerancia) {
			borrarMatriz(Atemp);
			return NULL;
		}
	}

	x[n - 1] = Atemp[0][n - 1] / Atemp[1][n - 1];
	for (int i = n - 2; i >= 0; i--)
		x[i] = (Atemp[0][i] - Atemp[2][i]*x[i + 1]) / Atemp[1][i];
	borrarMatriz(Atemp);

	return x;
}

/* Resuelve la ecuacion lineal Ax = b a traves del Metodo Iterativo de Gauss-Seidel.
Comentarios: El algoritmo puede no converger. Cuando la matriz es diagonal dominante, el algoritmo 
converge para cualquier condicion inicial.
Recibe:
   n - Las dimensiones de la matriz.
   A - Los datos de la matriz.
   b - El vector de terminos independientes.
   M - El numero maximo de iteraciones.
   x - Un vector inicial.
Regresa:
   x - El vector con una aproximacion a la solucion.
Devuelve el numero de iteraciones realizadas. Si la matriz tiene un 0 en la diagonal, devuelve -1. */
int GaussSeidel(int n, Matriz A, Vector b, int M, Vector x) {
	for (int k = 0; k < M; k++) {
		//Calculo del error
		double Error = 0;

		for (int i = 0; i < n; i++) {
			double Error_i = -b[i];

			for (int j = 0; j < n; j++)
				Error_i += A[i][j] * x[j];
			Error += Error_i * Error_i;
		}
		Error = sqrt(Error) / n;

		//Solucion encontrada
		if (Error < tolerancia)
			return k;

		//Iteracion del metodo
		for (int i = 0; i < n; i++) {
			if (fabs(A[i][i]) < tolerancia)
				return -1;

			x[i] = b[i];
			for (int j = 0; j < n; j++)
				if (j != i)
					x[i] -= A[i][j] * x[j];
			x[i] /= A[i][i];
		}
	}

	return M;
}

#endif // ECUACIONLINEAL_H_INCLUDED