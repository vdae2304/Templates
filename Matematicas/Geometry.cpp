/*********************************************************************************
* Implementacion de funciones geometricas en el plano.                           *
*********************************************************************************/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define epsilon 1e-9 //Precision.

struct point {
    double x, y;

    //Constructor.
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

//Regresa el punto de interseccion de dos rectas no paralelas AB y CD.
point lineLineIntersection(const point &A, const point &B, const point &C, const point &D) {
    point v = B - A, w = D - C;
    return A + v * (crossProduct(C - A, w) / crossProduct(v, w));
}

//Regresa el centro de la circunferencia que pasa por A, B y C.
point circumcenter(const point &A, const point &B, const point &C) {
    point MC = (A + B) / 2, MA = (B + C) / 2;
    return lineLineIntersection(MC, MC + rotate90ccw(A - B), MA, MA + rotate90ccw(C - B));
}

//Regresa las intersecciones de la recta AB con la circunferencia con centro O y radio r.
vector<point> lineCircleIntersection(const point &A, const point &B, const point &O, double r) {
    vector<point> ans;
    point v = B - A, w = A - O;
    double a = dotProduct(v, v), b = dotProduct(v, w), c = dotProduct(w, w) - r * r;
    double d = b * b - a * c;
    if (d >= -epsilon)
        ans.push_back(A + v * ((-b + sqrt(d + epsilon)) / a));
    if (d > epsilon)
        ans.push_back(A + v * ((-b - sqrt(d + epsilon)) / a));
    return ans;
}

//Regresa las intersecciones de las circunferencias con centros O1, O2 y radios r1, r2.
vector<point> circleCircleIntersection(const point &O1, double r1, const point &O2, double r2) {
    vector<point> ans;
    double d = dist(O1, O2);
    if (r1 + r2 >= d && d + min(r1, r2) >= max(r1, r2)) {
        point v = (O2 - O1) / d;
        double x = (d * d + r1 * r1 - r2 * r2) / (2 * d), y = sqrt(r1 * r1 - x * x);
        ans.push_back(O1 + v * x + rotate90ccw(v) * y);
        if (y > epsilon)
            ans.push_back(O1 + v * x - rotate90ccw(v) * y);
    }
    return ans;
}

//Regresa el area del triangulo con vertices A, B y C.
double areaTriangle(const point &A, const point &B, const point &C) {
    return fabs(crossProduct(B - A, C - A)) / 2;
}

//Regresa el area del poligono con vertices P[0], P[1], ... , P[n-1].
double areaPolygon(int n, const point P[]) {
    double area = 0;
    for (int i = 0; i < n; ++i) 
        area += crossProduct(P[i], P[(i + 1) % n]);
    return fabs(area) / 2;
}

//Regresa true si el poligono con vertices P es convexo.
bool isConvexPolygon(int n, const point P[]) {
    double orientation = crossProduct(P[1] - P[0], P[2] - P[1]);
    for (int i = 1; i < n; ++i) {
        int j = (i + 1) % n, k = (i + 2) % n;
        if (orientation * crossProduct(P[j] - P[i], P[k] - P[j]) < 0)
            return false;
    }
    return true;
}

//Imprime las coordenadas de un punto.
ostream& operator << (ostream &out, const point &P) {
    out << '(' << P.x << ',' << P.y << ')';
    return out;
}

int main() {
    //Datos de ejemplo.
    point P(3, 2), Q(-1, 4), A(-2, 1), B(2, 5), C(7, -2);
    double lambda = 2, theta = 3.1415926535 / 4, r1 = 4, r2 = 3;
    point convex[] = {point(-1,3), point(2,4), point(4,-1), point(-2,0)};
    point nonconvex[] = {point(-1,3), point(0,1), point(4,-1), point(-2,0)};
    //Operaciones fundamentales.
    cout << P << " + " << Q << " = " << P + Q << '\n';
    cout << P << " - " << Q << " = " << P - Q << '\n';
    cout << P << " * " << lambda << " = " << P * lambda << '\n';
    cout << P << " / " << lambda << " = " << P / lambda << "\n\n";
    //Producto punto y producto cruz.
    cout << P << " . " << Q << " = " << dotProduct(P, Q) << '\n';
    cout << P << " x " << Q << " = " << crossProduct(P, Q) << "\n\n";
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