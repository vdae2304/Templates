/*********************************************************************************
* Implementacion de funciones geometricas en el plano.                           *
*********************************************************************************/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#define PI  3.14159265358979323846 //Primeros 20 decimales de pi.
#define eps 1e-9                   //Precision.

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

//Regresa el vector rotado theta radianes en el sentido contrario de las manecillas 
//del reloj.
point rotateCCW(const point &P, double theta) {
    return point(P.x * cos(theta) - P.y * sin(theta), P.x * sin(theta) + P.y * cos(theta));
}

//Regresa la proyeccion ortogonal del vector P sobre el vector Q.
point projection(const point &P, const point &Q) {
    return Q * (dotProduct(P, Q) / dotProduct(Q, Q));
}

//Regresa la distancia de un punto P a la recta que pasa por A y B.
double distPointLine(const point &P, const point &A, const point &B) {
    return dist(P, A + projection(P - A, B - A));
}

//Regresa true si el segmento CD corta a la recta AB, i.e., si los puntos estan en lados 
//opuestos de la recta.
bool lineSegmentIntersect(const point &A, const point &B, const point &C, const point &D) {
    return crossProduct(B - A, C - A) * crossProduct(B - A, D - A) < 0;
}

//Regresa el punto de interseccion de dos rectas distintas no paralelas AB y CD.
point lineLineIntersection(const point &A, const point &B, const point &C, const point &D) {
    point v = B - A, w = D - C;
    return A + v * (crossProduct(C - A, w) / crossProduct(v, w));
}

//Regresa el centro de la circunferencia que pasa por A, B y C.
point circumcenter(const point &A, const point &B, const point &C) {
    point MC = (A + B) / 2, MA = (B + C) / 2;
    return lineLineIntersection(MC, MC + rotate90ccw(A - B), MA, MA + rotate90ccw(C - B));
}

//Regresa los puntos de interseccion de la recta que pasa por A y B con la circunferencia 
//con centro O y radio r.
vector<point> lineCircleIntersection(const point &A, const point &B, const point &O, double r) {
    vector<point> ans;
    point v = B - A;
    double a = dotProduct(v, v), b = dotProduct(A, v), c = dotProduct(A, A) - r * r;
    double d = b * b - a * c;
    if (d >= -eps)
        ans.push_back(A + v * ((-b + sqrt(d + eps)) / a));
    if (d > eps)
        ans.push_back(A + v * ((-b - sqrt(d + eps)) / a));
    return ans;
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

//Regresa true si el punto P esta en el interior del triangulo con vertices A, B y C.
bool pointInTriangle(const point &P, const point &A, const point &B, const point &C) {
    point G = (A + B + C) / 3;
    return !lineSegmentIntersect(A, B, P, G) && !lineSegmentIntersect(B, C, P, G) && 
           !lineSegmentIntersect(C, A, P, G);
}

//Regresa true si el poligono con vertices P (ordenados en el sentido de las manecillas del 
//reloj) es convexo.
bool isConvexPolygon(int n, const point P) {
    for (int i = 2; i < n; ++i) {
        if (crossProduct(P[i] - P[i - 1], P[i] - P[i - 1]) < 0)
            return false;
    return true;
}

//Regresa true si el punto Q esta en el interior del poligono convexo con vertices P.
//Un punto Q estara en el interior de un poligono no convexo si y solo cualquier rayo
//con origen en Q intersecta al poligono (en aristas) un numero impar de veces.
bool pointInConvexPolygon(const point &Q, int n, const point P[]) {
    point G = P[0];
    for (int i = 1; i < n; ++i)
    	G = G + P[i];
    G = G / n;
    for (int i = 1; i < n; ++i)
        if (lineSegmentIntersect(P[i - 1], P[i], Q, G))
            return false;
    return true;
}

int main() {
	return 0;
}