/*********************************************************************************
* Eliminacion Gaussiana para resolver sistemas lineales de ecuaciones.           *
* Complejidad: O(n^3)                                                            *
*********************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;
#define maxn 100 //Maximo numero de ecuaciones.

//Reduce la matriz aumentada [A | B] a [I | X] donde X es solucion de AX = B,
//con A de n x n y B de n x m. Regresa el determinante de A.
double GaussianElimination(int n, int m, double matrix[][maxn]) {
    double det = 1;
    for (int k = 0; k < n; ++k) {
        int r = k;
        for (int i = k + 1; i < n; ++i)
            if (fabs(matrix[i][k]) > fabs(matrix[r][k]))
                r = i;
        if (fabs(matrix[r][k]) < 1e-6)
            return 0;
        if (r != k) {
            for (int j = k; j < n + m; ++j)
                swap(matrix[k][j], matrix[r][j]);
            det *= -1;
        }
        det *= matrix[k][k];
        for (int j = n + m - 1; j >= k; --j) {
            matrix[k][j] /= matrix[k][k];
            for (int i = 0; i < n; ++i)
                if (i != k)
                    matrix[i][j] -= matrix[i][k] * matrix[k][j];
        }
    }
    return det;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    int n, m;
    double matrix[maxn][maxn];
    //Lee los datos de las ecuaciones.
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    	for (int j = 0; j < n + m; ++j)
    		cin >> matrix[i][j];
    //Imprime el determinante y la solucion.
    cout << "Determinante: " << GaussianElimination(n, m, matrix) << "\nSolucion:\n";
    for (int i = 0; i < n; ++i) {
    	for (int j = 0; j < m; ++j)
    		cout << matrix[i][j + n] << ' ';
    	cout << '\n';
    }
    return 0;
}
