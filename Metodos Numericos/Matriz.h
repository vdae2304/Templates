#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

/************************************************************************
* Operaciones con vectores                                              *
************************************************************************/

typedef double* Vector;

/* Reserva memoria para un vector de tamaño n. */
Vector crearVector(int n) {
	return new double[n];
}

/* Libera la memoria de un vector. */
void borrarVector(Vector v) {
	delete[] v;
}

/* Copia los valores de un vector v de tamaño n a otro. */
void copiarVector(int n, Vector v, Vector copia) {
	for (int i = 0; i < n; i++)
		copia[i] = v[i];
}

/* Inicializa un vector de tamaño n como el vector cero. */
void vectorCero(int n, Vector v) {
	for (int i = 0; i < n; i++)
		v[i] = 0;
}

/* Inicializa un vector de tamaño n como el i-esimo vector canonico. */
void vectorCanonico(int n, Vector v, int i) {
	vectorCero(n, v);
	v[i] = 1;
}

/* Inicializa un vector de tamaño n como la combinacion lineal de otros dos vectores. */
void combinacionLineal(int n, double a, Vector v, double b, Vector w, Vector res) {
	for (int i = 0; i < n; i++)
		res[i] = a*v[i] + b*w[i];
}

/* Calcula el producto punto de dos vectores. */
double productoPunto(int n, Vector v, Vector w) {
	double ppunto = 0;
	for (int i = 0; i < n; i++)
		ppunto += v[i] * w[i];
	return ppunto;
}


/************************************************************************
* Operaciones con matrices                                              *
************************************************************************/

typedef double** Matriz;

/* Reserva memoria para una matriz de m x n. */
Matriz crearMatriz(int m, int n) {
	Matriz A = new double*[m];
	A[0]     = new double[m * n];
	for (int i = 1; i < m; i++)
		A[i] = A[i - 1] + n;
	return A;
}

/* Libera la memoria de una matriz. */
void borrarMatriz(Matriz A) {
	delete[] A[0];
	delete[] A;
}

/* Copia los valores de una matriz A de m x n en otra. */
void copiarMatriz(int m, int n, Matriz A, Matriz copia) {
	copiarVector(m * n, A[0], copia[0]);
}

/* Inicializa una matriz A de m x n como la matriz cero. */
void matrizCero(int m, int n, Matriz A) {
	vectorCero(m * n, A[0]);
}

/* Inicializa una matriz de n x n como la matriz identidad. */
void matrizIdentidad(int n, Matriz A) {
	matrizCero(n, n, A);
	for (int i = 0; i < n; i++)
		A[i][i] = 1;
}

/* Devuelve la matriz transpuesta de una matriz A de m x n. */
void matrizTranspuesta(int m, int n, Matriz A, Matriz AT) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			AT[j][i] = A[i][j];
}

/* Devuelve el producto de una matriz A de m x n con un vector b de tamaño n. */
void productoMatrizVector(int m, int n, Matriz A, Vector b, Vector Ab) {
	vectorCero(m, Ab);
	for (int i = 0; i < m; i++) 
		for (int j = 0; j < n; j++)
			Ab[i] += A[i][j] * b[j];
}

/* Devuelve el producto de dos matrices A de l x m y B de m x n.
Observacion: La matriz AB debe ser distinta de las otras dos. */
void productoMatriz(int l, int m, int n, Matriz A, Matriz B, Matriz AB) {
	matrizCero(l, n, AB);
	for (int i = 0; i < l; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < m; k++)
				AB[i][j] += A[i][k] * B[k][j];
}

/* Inicializa una matriz de m x n como la combinacion lineal de otras dos matrices. */
void combinacionLineal(int m, int n, double a, Matriz A, double b, Matriz B, Matriz res) {
	combinacionLineal(m * n, a, A[0], b, B[0], res[0]);
}

#endif // MATRIZ_H_INCLUDED