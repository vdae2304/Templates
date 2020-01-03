/*********************************************************************************
* Implementacion de funciones geometricas en el plano.                           *
*********************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

typedef double T; //int o double

struct point {
    T x, y;

    //Constructor.
    point(T _x, T _y) {
        x = _x;
        y = _y;
    }

    //Regresa la suma de dos puntos.
    point operator + (const point &P) {
        return point(x + P.x, y + P.y);
    }

    //Regresa la resta de dos puntos.
    point operator - (const point &P) {
        return point(x - P.x, y - P.y);
    }

    //Regresa el producto por un escalar.
    point operator * (T lambda) {
        return point(x * lambda, y * lambda);
    }

    //Regresa el cociente entre un escalar.
    point operator / (T lambda) {
        return point(x / lambda, y / lambda);
    }
};

//Regresa el producto punto.
T dotProduct(point P, point Q) {
    return P.x*Q.x + P.y*Q.y;
}

//Regresa la norma al cuadrado de un vector.
T norm2(point P) {
    return dotProduct(P, P);
}

//Regresa la distancia al cuadrado entre dos puntos.
T dist2(point P, point Q) {
    return norm2(P - Q);
}

//Regresa el angulo entre dos vectores.
double angle(point P, point Q) {
	return acos(dotProduct(P, Q) / sqrt(norm2(P) * norm2(Q)));
}

point CrossProduct(point P, point Q) {
	return point(P.y*Q.z - P.z*Q.y, P.z*Q.x - P.x*Q.z, P.x*Q.y - P.y*Q.x);
}

point projection(point P, point Q) {
	return (DotProduct(P, Q)/DotProduct(Q, Q)) * Q;
}

int main() {
	return 0;
}