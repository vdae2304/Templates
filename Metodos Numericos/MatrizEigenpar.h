#ifndef MATRIZEIGENPAR_H_INCLUDED
#define MATRIZEIGENPAR_H_INCLUDED

#include "Matriz.h"
#include "MatrizFactorizacion.h"
#include <cmath>

//Precision
#ifndef tolerancia 
#define tolerancia 1e-9
#endif

/* Metodo de la potencia para calcular el eigenpar asociado al eigenvalor mas grande en valor
absoluto de una matriz.
Recibe: 
   n - Las dimensiones de la matriz.
   A - Los datos de la matriz.
   M - El numero maximo de iteraciones.
   v - Un vector inicial.
Regresa: 
   v - El eigenvector.
   c - El eigenvalor.
Devuelve el numero de iteraciones realizadas. */
int MetodoPotencia(int n, Matriz A, int M, Vector v, double &c) {
	Vector Av = crearVector(n);
	productoMatrizVector(n, n, A, v, Av);

	for (int k = 0; k < M; k++) {
		//Calculo del error
		double Error = 0;
		for (int i = 0; i < n; i++)
			Error += (Av[i] - c*v[i]) * (Av[i] - c*v[i]);
		Error = sqrt(Error) / n;

		//Eigenpar encontrado
		if (Error < tolerancia) {
			borrarVector(Av);
			return k;
		}

		//Iteracion del metodo
		double Avnorma = sqrt(productoPunto(n, Av, Av));
		for (int i = 0; i < n; i++)
			v[i] = Av[i] / Avnorma;
		productoMatrizVector(n, n, A, v, Av);
		c = productoPunto(n, v, Av);
	}

	borrarVector(Av);
	return M;
}

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
	Matriz tempV = crearMatriz(n, n);
	matrizIdentidad(n, V);
	copiarMatriz(n, n, A, U);

	for (int k = 0; k < M; k++) {
		//Mayor elemento debajo de la diagonal
		double umax = 0;
		for (int r = 0; r < n; r++)
			for (int c = 0; c < r; c++)
				if (fabs(U[r][c]) > umax)
					umax = U[r][c];

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
		productoMatriz(n, n, n, tempV, Q, V);
		productoMatriz(n, n, n, R, Q, U);
	}

	borrarMatriz(Q);
	borrarMatriz(R);
	borrarMatriz(tempV);
	return M;
}

/* Calcula la descomposicion en valores singulares A = USV^T donde A es una matriz cuadrada, 
U y V son matrices ortonormales, y S es una matriz diagonal cuyos elementos en la diagonal son los 
valores singulares de A.
Recibe: 
   n - Las dimensiones de la matriz.
   A - Los datos de la matriz.
   M - El numero maximo de iteraciones.
Regresa: 
   U, V - Los datos de las matrices ortonormales.
   S    - Los datos de la matriz diagonal.
Devuelve el numero de iteraciones realizadas. */
int FactorizacionSVD(int n, Matriz A, int M, Matriz U, Matriz S, Matriz V) {
	Matriz AT  = crearMatriz(n, n);
	Matriz ATA = crearMatriz(n, n);
	matrizTranspuesta(n, n, A, AT);
	productoMatriz(n, n, n, AT, A, ATA);

	int k = MetodoJacobi(n, ATA, M, V, S);
	for (int i = 0; i < n; i++)
		S[i][i] = sqrt(S[i][i]);
	productoMatriz(n, n, n, A, V, U);

	for (int j = 0; j < n; j++) {
		double Uj = 0;
		for (int i = 0; i < n; i++)
			Uj += U[i][j] * U[i][j];
		Uj = sqrt(Uj);
		for (int i = 0; i < n; i++)
			U[i][j] /= Uj;
	}

	borrarMatriz(AT);
	borrarMatriz(ATA);
	return k;
}

#endif // MATRIZEIGENPAR_H_INCLUDED