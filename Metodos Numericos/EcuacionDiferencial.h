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
Devuelve un vector con los valores de la solucion en los puntos de la discretizacion */
Vector RungeKutta(int n, Vector x, double (*f)(double, double), double y0) {
	Vector y = crearVector(n);
	
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
   y'(x) = f(n, x, y(x)),    y(x0) = y0
donde y es un vector de tamaño n y f es una funcion vectorial.
Recibe:
   m  - El tamaño de la particion
   x  - La discretizacion del intervalo de solucion
   n  - El numero de ecuaciones
   f  - La funcion que define la ecuacion
   y0 - La condicion inicial
Devuelve una matriz donde cada columna contiene los valores de la solucion correspondiente evaluada
en los puntos de la discretizacion */
Matriz SistemaRungeKutta(int m, Vector x, int n, Vector (*f)(int, double, Vector), Vector y0) {
	Matriz y = crearMatriz(m, n);

	for (int j = 0; j < n; j++)
		y[0][j] = y0[j];

	Vector ytemp = crearVector(n);
	for (int i = 1; i < m; i++) {
		double h = x[i] - x[i - 1];

		Vector K1 = f(n, x[i - 1], y[i - 1]);
		combinacionLineal(n, 1, y[i - 1], h/2, K1, ytemp);
		Vector K2 = f(n, x[i - 1] + h/2, ytemp);
		combinacionLineal(n, 1, y[i - 1], h/2, K2, ytemp);
		Vector K3 = f(n, x[i - 1] + h/2, ytemp);
		combinacionLineal(n, 1, y[i - 1], h, K3, ytemp);
		Vector K4 = f(n, x[i - 1] + h, ytemp);

		combinacionLineal(n, 1, y[i - 1], h/6, K1, y[i]);
		combinacionLineal(n, 1, y[i], h/3, K2, y[i]);
		combinacionLineal(n, 1, y[i], h/3, K3, y[i]);
		combinacionLineal(n, 1, y[i], h/6, K4, y[i]);
	}

	borrarVector(ytemp);
	return y;
}

#endif // ECUACIONDIFERENCIAL_H_INCLUDED
