/*********************************************************************************
* Eliminacion Gaussiana para resolver sistemas lineales de ecuaciones.           *
* Complejidad: O(n^3)                                                            *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define maxn 100 //Maximo numero de ecuaciones-incognitas.

int n, m;                     //Dimensiones.
double AugMatrix[maxn][maxn]; //Matriz aumentada.

//Encuentra la forma escalonada reducida de la matriz aumentada [A | B] 
//con A de n x n y B de n x m. Regresa el determinante de A.
double GaussianElimination() {
    double det = 1;
    for (int k = 0; k < n; ++k) {
        int r = k;
        for (int i = k + 1; i < n; ++i)
            if (fabs(AugMatrix[i][k]) > fabs(AugMatrix[r][k]))
                r = i;

        if (fabs(AugMatrix[r][k]) < 1e-9)
            return 0;
        if (r != k) {
            for (int j = k; j < n + m; ++j)
                swap(AugMatrix[k][j], AugMatrix[r][j]);
            det *= -1;
        }
        det *= AugMatrix[k][k];

        for (int j = n + m - 1; j >= k; --j) {
            AugMatrix[k][j] /= AugMatrix[k][k];
            for (int i = 0; i < n; ++i)
                if (i != k)
                    AugMatrix[i][j] -= AugMatrix[i][k] * AugMatrix[k][j];
        }
    }
    return det;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
    	for (int j = 0; j < n + m; ++j)
    		cin >> AugMatrix[i][j];
    
    cout << "Determinante: " << GaussianElimination() << "\nSolucion:\n";
    for (int i = 0; i < n; ++i) {
    	for (int j = 0; j < m; ++j)
    		cout << AugMatrix[i][j + n] << ' ';
    	cout << '\n';
    }

    return 0;
}
