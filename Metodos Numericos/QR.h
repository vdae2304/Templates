#ifndef QR_H_INCLUDED
#define QR_H_INCLUDED
#include "Matriz.h"
#include <cmath>

//Precision
#ifndef tolerancia 
#define tolerancia 1e-9
#endif

/* Proceso de Gram-Schmidt para calcular la factorizacion QR de una matriz.
Recibe: 
   n, m - Las dimensiones de la matriz   
   A    - Los datos de la matriz
Regresa: 
   Q - Una matriz ortonormal
   R - Una matriz triangular superior
Devuelve true si la factorizacion existe y false en caso contrario*/
bool GramSchmidt(int n, int m, double **A, double **Q, double **R) {
	copiarMatriz(n, m, A, Q);
	matrizCero(m, m, R);

	for (int i = 0; i < m; i++) {
		for (int k = 0; k < n; k++)
			R[i][i] += Q[k][i] * Q[k][i];
		R[i][i] = sqrt(R[i][i]);
		
		if (fabs(R[i][i]) < tolerancia)
			return false;

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