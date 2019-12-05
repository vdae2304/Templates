#ifndef INTEGRACION_H_INCLUDED
#define INTEGRACION_H_INCLUDED
#include "Matriz.h"

/* Metodo de Romberg para calcular la integral de f sobre una particion de tamaño 2^n del intervalo [a, b] */
double MetodoRomberg(double (*f)(double), double a, double b, int n) {	
	Matriz R = crearMatriz(n + 1, n + 1);
	matrizCero(n + 1, n + 1, R);

	//Regla del trapecio
	R[0][0] = (b - a)*(f(a) + f(b)) / 2;

	for (int i = 1; i <= n; i++) {
		double h = (b - a) / (1 << i);
		for (int k = 1; k <= 1 << (i - 1); k++)
			R[i][0] += f(a + (2*k - 1)*h);

		R[i][0] = R[i - 1][0]/2 + h*R[i][0];
	}
	
	//Extrapolacion de Richardson
	for (int j = 1; j <= n; j++) 
		for (int i = j; i <= n; i++)
			R[i][j] = R[i][j - 1] + (R[i][j - 1] - R[i - 1][j - 1]) / ((1 << (2*j)) - 1);

	double integral = R[n][n];
	borrarMatriz(R);
	return integral;
}

#endif // INTEGRACION_H_INCLUDED
