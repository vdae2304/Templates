#ifndef ECUACIONDIFERENCIAL_H_INCLUDED
#define ECUACIONDIFERENCIAL_H_INCLUDED
#include "Matriz.h"

/* Metodo de Runge-Kutta de orden 4 para resolver la ecuacion diferencial ordinaria
   y'(x) = f(x, y(x)),      y(x0) = y0 
Recibe:
   n  - El tamaño de la particion
   x  - La discretizacion del intervalo de solucion
   f  - La funcion que define la ecuacion 
   y0 - La condicion inicial   
Devuelve un apuntador con los valores de la solucion en los puntos de la discretizacion */
double *RungeKutta(int n, double *x, double (*f)(double, double), double y0) {
	double *y = new double[n];
	
	y[0] = y0;
	for (int i = 1; i < n; i++) {
		double h = x[i] - x[i - 1];

		double K1 = h*f(x[i - 1], y[i - 1]);
		double K2 = h*f(x[i - 1] + h/2, y[i - 1] + K1/2);
		double K3 = h*f(x[i - 1] + h/2, y[i - 1] + K2/2);
		double K4 = h*f(x[i - 1] + h, y[i - 1] + K3);

		y[i] = y[i - 1] + (K1 + 2*K2 + 2*K3 + K4)/6;
	}

	return y;
}

/* Metodo de Runge-Kutta de orden 4 para resolver el sistema de ecuaciones diferenciales
   yi'(x) = fi(x, y1(x),...,yn(x)),    yi(x0) = yi0       i = 0,...,n-1
Recibe:
   n  - El numero de ecuaciones
   m  - El tamaño de la particion
   x  - La discretizacion del intervalo de solucion
   f  - Las funciones que definen la ecuacion
   y0 - Las condiciones iniciales
Devuelve una matriz donde cada renglon contiene los valores de la solucion correspondiente evaluada
en los puntos de la discretizacion */
double **SistemaRungeKutta(int n, int m, double *x, double (**f)(double, double *), double *y0) {
	double **y = crearMatriz(n, m);

	for (int i = 0; i < n; i++)
		y[i][0] = y0[i];

	double *ytemp = new double[n];
	double *K     = new double[n];
	double c[8]   = {0, 0.5, 0.5, 1, 1.0/6, 1.0/3, 1.0/3, 1.0/6};
	
	for (int j = 1; j < m; j++) {
		double h = x[j] - x[j - 1];
		for (int i = 0; i < n; i++)
			y[i][j] = y[i][j - 1];

		for (int k = 0; k < 4; k++) {
			for (int i = 0; i < n; i++)
				ytemp[i] = y[i][j - 1] + c[k]*K[i];
			for (int i = 0; i < n; i++) {
				K[i]     = h*f[i](x[j - 1] + c[k]*h, ytemp);
				y[i][j] += c[k + 4]*K[i];
			}
		}
	}

	delete[] ytemp;
	delete[] K;
	return y;
}

#endif // ECUACIONDIFERENCIAL_H_INCLUDED
