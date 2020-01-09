/*********************************************************************************
* Implementacion de funciones geometricas en el plano.                           *
*********************************************************************************/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define epsilon 1e-6 //Precision.

struct point {
    double x, y;
};
typedef const point cpoint;

point operator + (cpoint &P, cpoint &Q) {
    return point{P.x + Q.x, P.y + Q.y};
}

point operator - (cpoint &P, cpoint &Q) {
    return point{P.x - Q.x, P.y - Q.y};
}

point operator * (cpoint &P, double c) {
    return point{P.x * c, P.y * c};
}

point operator / (cpoint &P, double c) {
    return point{P.x / c, P.y / c};
}

//Regresa el producto punto de dos vectores. Es 0 cuando son ortogonales.
double dot(cpoint &P, cpoint &Q) {
    return P.x * Q.x + P.y * Q.y;
}

//Regresa la componente z del producto cruz de dos vectores. Es 0 cuando son paralelos.
double cross(cpoint &P, cpoint &Q) {
    return P.x * Q.y - P.y * Q.x;
}

//Regresa la distancia euclidiana al origen de un punto.
double norm(cpoint &P) {
    return sqrt(dot(P, P));
}

//Regresa la distancia euclidiana entre dos puntos.
double dist(cpoint &P, cpoint &Q) {
    return norm(P - Q);
}

//Regresa el vector rotado 90 grados en el sentido contrario de las manecillas del reloj.
point rotate90ccw(cpoint &P) {
    return point{-P.y, P.x};
}

//Regresa el vector rotado theta radianes en sentido contrario de las manecillas del reloj.
point rotateCCW(cpoint &P, double theta) {
    return point{P.x*cos(theta) - P.y*sin(theta), P.x*sin(theta) + P.y*cos(theta)};
}

//Regresa la proyeccion ortogonal del vector P sobre el vector Q.
point projection(cpoint &P, cpoint &Q) {
    return Q * (dot(P, Q) / dot(Q, Q));
}

//Regresa la distancia del punto P a la recta que pasa por A y B.
double distPointLine(cpoint &P, cpoint &A, cpoint &B) {
    return dist(P, A + projection(P - A, B - A));
}

//Regresa true si la recta que pasa por A y B corta al segmento con extremos C y D.
bool lineSegmentIntersection(cpoint &A, cpoint &B, cpoint &C, cpoint &D) {
    return cross(B - A, C - A) * cross(B - A, D - A) < 0;
}

//Regresa el punto de interseccion de dos rectas no paralelas AB y CD.
point lineLineIntersection(cpoint &A, cpoint &B, cpoint &C, cpoint &D) {
    point v = B - A, w = D - C;
    return A + v * (cross(C - A, w) / cross(v, w));
}

//Regresa el centro de la circunferencia que pasa por A, B y C.
point circumcenter(cpoint &A, cpoint &B, cpoint &C) {
    point AB = (A + B) / 2, BC = (B + C) / 2;
    return lineLineIntersection(AB, AB + rotate90ccw(A - B), BC, BC + rotate90ccw(C - B));
}

//Regresa las intersecciones de la recta AB con la circunferencia con centro O y radio r.
vector<point> lineCircleIntersection(cpoint &A, cpoint &B, cpoint &O, double r) {
    vector<point> ans;
    point v = B - A, w = A - O;
    double a = dot(v, v), b = dot(v, w), c = dot(w, w) - r*r;
    double d = b*b - a*c;
    if (d >= -epsilon)
        ans.push_back(A + v * ((-b + sqrt(d + epsilon))/a));
    if (d > epsilon)
        ans.push_back(A + v * ((-b - sqrt(d + epsilon))/a));
    return ans;
}

//Regresa las intersecciones de las circunferencias con centros O1, O2 y radios r1, r2.
vector<point> circleCircleIntersection(cpoint &O1, double r1, cpoint &O2, double r2) {
    vector<point> ans;
    double d = dist(O1, O2);
    if (r1 + r2 >= d && d + min(r1, r2) >= max(r1, r2)) {
        point v = (O2 - O1) / d;
        double x = (d*d + r1*r1 - r2*r2) / (2*d), y = sqrt(r1*r1 - x*x);
        ans.push_back(O1 + v * x + rotate90ccw(v) * y);
        if (y > epsilon)
            ans.push_back(O1 + v * x - rotate90ccw(v) * y);
    }
    return ans;
}

//Regresa 1, 0, -1 dependiendo si el punto Q esta fuera, sobre o dentro del poligono 
//(posiblemente no convexo) con vertices P.
int pointInPolygon(cpoint &Q, int n, cpoint P[]) {
    int numCrossings = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        if (distPointLine(Q, P[i], P[j]) < epsilon && 
            fabs(dist(P[i], Q) + dist(Q, P[j]) - dist(P[i], P[j])) < epsilon)
            return 0;
        if (cross(P[i] - Q, P[j] - Q) * ((Q.y <= P[j].y) - (Q.y <= P[i].y)) > 0)
            numCrossings++;
    }
    return numCrossings % 2 ? 1 : -1;
}

//Regresa el area con signo del poligono (posiblemente no convexo) con vertices P.
double areaPolygon(int n, cpoint P[]) {
    double area = 0;
    for (int i = 0; i < n; ++i) 
        area += cross(P[i], P[(i+1)% n]);
    return area / 2;
}

//Regresa true si el poligono con vertices P es convexo.
bool isConvexPolygon(int n, cpoint P[]) {
    double orientation = cross(P[1] - P[0], P[2] - P[1]);
    for (int i = 1; i < n; ++i) 
        if (orientation * cross(P[(i+1)% n] - P[i], P[(i+2)% n] - P[(i+1)% n]) < 0)
            return false;
    return true;
}

//Imprime las coordenadas de un punto.
ostream& operator << (ostream &out, cpoint &P) {
    return out << '(' << P.x << ',' << P.y << ')';
}

int main() {
    //Datos de ejemplo.
    point P(3, 2), Q(-1, 4), A(-2, 1), B(2, 5), C(7, -2);
    double lambda = 2, theta = 3.1415926535 / 4, r1 = 4, r2 = 3;
    point convex[] = {point(-1,3), point(2,4), point(4,-1), point(-2,0)};
    point nonconvex[] = {point(-1,3), point(0,1), point(4,-1), point(-2,0)};
    //Imprime la norma y la distancia.
    cout << '|' << P << "| = " << norm(P) << '\n';
    cout << "dist(" << P << ", " << Q << ") = " << dist(P, Q) << "\n\n";
    //Imprime el angulo y el vector rotado 90 y 45 grados.
    cout << "<(" << P << ", " << Q << ") = " << angle(P, Q) << '\n';
    cout << "rotar90" << P << " = " << rotate90ccw(P) << '\n';
    cout << "rotar(" << P << ", " << theta << ") = " << rotateCCW(P, theta) << "\n\n";
    //Imprime la proyeccion y la distancia punto-recta.
    cout << "proy(" << P << ", " << Q << ") = " << projection(P, Q) << '\n';
    cout << "dist(" << P << ", l(" << A << ',' << B << ")) = " << distPointLine(P, A, B) << "\n\n";
    //Interseccion recta-segmento y recta-recta.
    cout << "Interseccion(l(" << A << ',' << B << "), s(" << P << ',' << Q << ")) = " << (lineSegmentIntersect(A, B, P, Q) ? "Si" : "No") << '\n';
    cout << "Interseccion(l(" << B << ',' << C << "), s(" << P << ',' << Q << ")) = " << (lineSegmentIntersect(B, C, P, Q) ? "Si" : "No") << '\n';
    cout << "Interseccion(l(" << A << ',' << B << "), l(" << P << ',' << Q << ")) = " << lineLineIntersection(A, B, P, Q) << "\n\n";
    //Circuncentro.
    cout << "Circuncentro(" << A << ", " << B << ", " << C << ") = " << circumcenter(A, B, C) << "\n\n";
    //Interseccion recta-circulo y circulo-circulo.
    cout << "Interseccion(l(" << A << ',' << B << "), C(" << P << ',' << r1 << ")) : ";
    for (point x : lineCircleIntersection(A, B, P, r1))
        cout << x << ' ';
    cout << "\nInterseccion(C(" << P << ',' << r1 << "), C(" << Q << ',' << r2 << ")) : ";
    for (point x : circleCircleIntersection(P, r1, Q, r2))
        cout << x << ' ';
    //Area de triangulo y poligono.
    cout << "\n\nArea(" << A << ", " << B << ", " << C << ") = " << areaTriangle(A, B, C) << '\n';
    cout << "Area(" << convex[0] << ", " << convex[1] << ", " << convex[2] << ", " << convex[3] << ") = " << areaPolygon(4, convex) << '\n';
    cout << "Area(" << nonconvex[0] << ", " << nonconvex[1] << ", " << nonconvex[2] << ", " << nonconvex[3] << ") = " << areaPolygon(4, nonconvex) << "\n\n";
    //Verifica si es convexo o no.
    cout << "Es convexo(" << convex[0] << ", " << convex[1] << ", " << convex[2] << ", " << convex[3] << ") = " << (isConvexPolygon(4, convex) ? "Si" : "No") << '\n';
    cout << "Es convexo(" << nonconvex[0] << ", " << nonconvex[1] << ", " << nonconvex[2] << ", " << nonconvex[3] << ") = " << (isConvexPolygon(4, nonconvex) ? "Si" : "No") << '\n';
    return 0;
}