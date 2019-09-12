/*********************************************************************
* Algoritmo de Eliminacion Gaussiana para resolver sistemas lineales *
* de ecuaciones.                                                     *
* Complejidad: O(n^3)                                                *
*********************************************************************/
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define maxn 100
#define epsilon 1e-10

//Recibe una matriz aumentada [A | B] con A de n x n y B de n x m.
//Transforma la matriz a [I | X] donde X es solucion (si existe) de AX = B.
//Regresa el determinante de la matriz A.
double EliminacionGaussiana(int n, int m, double AugMatrix[][maxn]) {
	double det = 1;
	//Forma escalonada de la matriz
	for (int k = 0; k < n; k++) {				
		int r = k;
		for (int i = k + 1; i < n; i++)
			if (fabs(AugMatrix[i][k]) > fabs(AugMatrix[r][k]))
				r = i;		
		if (fabs(AugMatrix[r][k]) < epsilon)
			return 0;
		if (r != k) {
			for (int j = k; j < n + m; j++)
				swap(AugMatrix[k][j], AugMatrix[r][j]);
			det *= -1;			
		}		
		
		det *= AugMatrix[k][k];
		for (int j = k + 1; j < n + m; j++) {
			AugMatrix[k][j] /= AugMatrix[k][k];
			for (int i = k + 1; i < n; i++)
				AugMatrix[i][j] -= AugMatrix[i][k] * AugMatrix[k][j];									
		}		
		AugMatrix[k][k] = 1;
		for (int i = k + 1; i < n; i++)
			AugMatrix[i][k] = 0;
	}
	//Forma escalonada reducida de la matriz
	for (int k = n - 1; k > 0; k--) 
		for (int i = 0; i < k; i++) {						
			for (int j = n; j < n + m; j++)
				AugMatrix[i][j] -= AugMatrix[i][k] * AugMatrix[k][j];
			AugMatrix[i][k] = 0;
		}		
	return det;
}

int main() {
	const int n = 3;
	double MatInversa[n][maxn] = {{ 2,  1, -1,  1, 0, 0},
					 			  {-3, -1,  2,  0, 1, 0},
						  		  {-2,  1,  2,  0, 0, 1}};
	cout << EliminacionGaussiana(n, n, MatInversa) << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << MatInversa[i][j + n] << ' ';
		cout << '\n';
	}
	return 0;
}