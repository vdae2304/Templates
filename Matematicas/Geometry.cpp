/*********************************************************************************
* Implementacion de funciones geometricas en el plano.                           *
*********************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.14159265358979323846

struct point {
    double x, y;

    point(double Px, double Py) : x(Px), y(Py) {} 

    //Regresa la suma de dos vectores.
    point operator + (const point &P) const {
        return point(x + P.x, y + P.y);
    }

    //Regresa la resta de dos vectores.
    point operator - (const point &P) const {
        return point(x - P.x, y - P.y);
    }

    //Regresa el producto por un escalar.
    point operator * (double lambda) const {
        return point(x * lambda, y * lambda);
    }

    //Regresa el cociente entre un escalar.
    point operator / (double lambda) const {
        return point(x / lambda, y / lambda);
    }
};

//Regresa el producto punto de dos vectores.
double dotProduct(const point &P, const point &Q) {
    return P.x * Q.x + P.y * Q.y;
}

//Regresa la componente en z del producto cruz de dos vectores.
double crossProduct(const point &P, const point &Q) {
    return P.x * Q.y - P.y * Q.x;
}

//Regresa la norma de un vector.
double norm(const point &P) {
    return sqrt(dotProduct(P, P));
}

//Regresa la distancia euclidiana entre dos puntos.
double dist(const point &P, const point &Q) {
    return norm(P - Q);
}

//Regresa el angulo en radianes entre dos vectores. Para verificar si son ortogonales 
//(o paralelos), es mas rapido comprobar si su producto punto (resp. cruz) es cero.
double angle(const point &P, const point &Q) {
    return acos(dotProduct(P/norm(P), Q/norm(Q)));
}

//Regresa el vector rotado 90 grados en el sentido contrario de las manecillas del reloj.
point rotate90ccw(const point &P) {
    return point(-P.y, P.x);
}

//Regresa el vector rotado theta (radianes o grados) en el sentido contrario de las manecillas del reloj.
point rotate_ccw(const point &P, double theta, bool radians = true) {
    if (!radians)
        theta *= PI/180;
    return point(P.x*cos(theta) - P.y*sin(theta), P.x*sin(theta) + P.y*cos(theta));
}

//Regresa el area del triangulo con vertices A, B y C.
double areaTriangle(const point &A, const point &B, const point &C) {
    return fabs(crossProduct(B - A, C - A)) / 2;
}

//Regresa el area del poligono con vertices P[0], P[1], ... , P[n-1].
double areaPolygon(int n, const point P[]) {
    double area = P[n - 1].x * P[0].y - P[0].x * P[n - 1].y;
    for (int i = 0; i < n - 1; ++i)
        area += P[i].x * P[i + 1].y - P[i + 1].x * P[i].y;
    return fabs(area) / 2;
}

//Regresa la proyeccion del vector P sobre el vector Q.
point projection(const point &P, const point &Q) {
    return Q * (dotProduct(P, Q) / dotProduct(Q, Q));
}

//Regresa la distancia de un punto P a la recta que pasa por A y B.
double distPointLine(const point &P, const point &A, const point &B) {
    return dist(P, A + projection(P - A, B - A));
}

//Regresa true si el segmento CD corta a la recta que pasa por A y B, i.e., si los puntos
//estan en lados opuestos de la recta.
bool segmentLineIntersects(const point &A, const point &B, const point &C, const point &D) {
    return crossProduct(B - A, C - A) * crossProduct(B - A, D - A) < 0;
}

//Regresa el punto de interseccion de dos rectas no paralelas que pasan por A, B y C, D.
point lineLineIntersection(const point &A, const point &B, const point &C, const point &D) {
    point v = B - A, w = D - C;
    return A + v * (crossProduct(C - A, w) / crossProduct(v, w));
}

//Regresa el centro de la circunferencia que pasa por A, B y C.
point circumcenter(const point &A, const point &B, const point &C) {
    point MC = (A + B) / 2, MA = (B + C) / 2;
    return lineLineIntersection(MC, MC + rotate90ccw(A - B), MA, MA + rotate90ccw(C - B));
}

//Regresa true si el punto P esta en el interior del triangulo con vertices A, B y C.
bool pointInTriangle(const point &P, const point &A, const point &B, const point &C) {
    ;
}

//Regresa true si el punto Q esta en el interior del poligono convexo con vertices P.
//Para verificar si
bool pointInPolygon(const point &Q, int n, const point P[]) {
    ;
}

int main() {
	return 0;
}