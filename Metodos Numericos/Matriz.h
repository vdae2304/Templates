#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

/* Reserva memoria para una matriz de n x m */
double **crearMatriz(int n, int m) {
	double **A = new double *[n];
	A[0] = new double[n * m];
	for (int i = 1; i < n; i++)
		A[i] = A[i - 1] + m;
	return A;
}

/* Libera la memoria de una matriz */
void borrarMatriz(double **A) {
	delete[] A[0];
	delete[] A;
}

/* Copia los valores de una matriz A de n x m en otra */
void copiarMatriz(int n, int m, double **A, double **copia) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			copia[i][j] = A[i][j];
}

/* Inicializa una matriz A de n x m como la matriz cero */
void matrizCero(int n, int m, double **A) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			A[i][j] = 0;
}

/* Inicializa una matriz I de n x n como la matriz identidad */
void matrizIdentidad(int n, double **I) {
	MatrizCero(n, n, I);
	for (int i = 0; i < n; i++)
		I[i][i] = 1;
}

/* Devuelve la transpuesta de una matriz A de n x m */
void transpuesta(int n, int m, double **A, double **AT) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			AT[j][i] = A[i][j];
}

/* Regresa el producto de dos matrices A de n x m y B de m x l */
void producto(int n, int m, int l, double **A, double **B, double **AB) {
	matrizCero(n, l, AB);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < l; j++)
			for (int k = 0; k < m; k++)
				AB[i][j] += A[i][k] * B[k][j];
}


#endif // MATRIZ_H_INCLUDED
