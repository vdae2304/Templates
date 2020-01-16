/*********************************************************************************
* Eliminacion de Gauss-Jordan.                                                   *
* Complejidad: O(n^3)                                                            *
*********************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;
#define maxn 100 //Maximo numero de renglones y columnas.

//Encuentra la forma escalonada reducida de la matriz A de m x n.
void GaussJordan(int m, int n, double matrix[][maxn]) {
    for (int r = 0, c = 0; c < n; ++c) {
        int pivot = r;
        for (int i = r + 1; i < m; ++i)
            if (fabs(matrix[pivot][c]) < fabs(matrix[i][c]))
                pivot = i;
        if (fabs(matrix[pivot][c]) < 1e-6)
            continue;
        if (pivot != r)
            for (int j = c; j < n; ++j)
                swap(matrix[r][j], matrix[pivot][j]);
        for (int j = n - 1; j >= c; --j) {
            matrix[r][j] /= matrix[r][c];
            for (int i = 0; i < m; ++i)
                if (i != r)
                    matrix[i][j] -= matrix[i][c] * matrix[r][j];
        }
        ++r;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    int m, n;
    double matrix[maxn][maxn];
    //Lee los datos de la matriz.
    cin >> m >> n;
    for (int i = 0; i < m; ++i)
    	for (int j = 0; j < n; ++j)
    		cin >> matrix[i][j];
    //Imprime la forma escalonada reducida.
    GaussJordan(m, n, matrix);
    for (int i = 0; i < m; ++i) {
    	for (int j = 0; j < n; ++j)
    		cout << matrix[i][j] << ' ';
    	cout << '\n';
    }
    return 0;
}
