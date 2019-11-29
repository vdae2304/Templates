#ifndef NEWTONRAPHSON_H_INCLUDED
#define NEWTONRAPHSON_H_INCLUDED
#include <cmath>

//Precision
#define epsilon 1e-9;

/* Metodo de Newton-Raphson para resolver la ecuacion f(x) = 0
Recibe:
   f    - Un apuntador de una funcion
   df   - Un apuntador de la derivada de la funcion
   xk   - Un valor inicial
   maxk - El maximo numero de iteraciones
Si el algoritmo converge, devuelve una aproximacion a la raiz */
void NewtonRaphson(double (*f)(double), double (*df)(double), double xk, int maxk) {
	for (int k = 0; k < maxk; k++) {
		if (fabs(f(xk)) < epsilon) 
			break;
		
		xk -= f(xk) / df(xk);
	}
	return xk;
}

/* Metodo de la secante para resolver la ecuacion f(x) = 0
Recibe:
   f         - Un apuntador de una funcion
   xk, x_nxt - Valores iniciales
   maxk      - El maximo numero de iteraciones
Si el algoritmo converge, devuelve una aproximacion a la raiz */
void MetodoSecante(double (*f)(double), double xk, double x_nxt, int maxk) {	
	for (int k = 0; k < maxk; k++) {
		if (fabs(f(xk)) < epsilon) 
			break;
		
		double x = x_nxt - (x_nxt - xk)/(f(x_nxt) - f(xk)) * f(x_nxt);
		xk       = x_nxt;
		x_nxt    = x;
	}
	return xk;
}

#endif // NEWTONRAPHSON_H_INCLUDED
