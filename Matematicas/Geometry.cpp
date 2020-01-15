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

//Regresa la distancia euclidiana de un punto al origen.
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

//Regresa 1, 0, -1 dependiendo si el punto Q esta dentro, sobre o fuera del poligono 
//(posiblemente no convexo) con vertices P.
int pointInPolygon(cpoint &Q, int n, cpoint P[]) {
    int numCrossings = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        if (fabs(dist(P[i], Q) + dist(Q, P[j]) - dist(P[i], P[j])) < epsilon)
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

int main() {
    point poly1[] = {{0.0,0.0}, {-2.0,1.0}, {0.0,2.0}, {1.0,4.0}, {2.0,1.0}};  
    point poly2[] = {{0.0,0.0}, {-2.0,1.0}, {-2.0,3.0}, {1.0,4.0}, {2.0,1.0}}; 
    //distPointLine test.
    cout << distPointLine({0.0,3.0}, {0.0,2.0}, {2.0,3.0}) << '\n'; //0.89
    //lineSegmentIntersection test.
    cout << lineSegmentIntersection({0.0,2.0}, {2.0,3.0}, {0.0,3.0}, {2.0,0.0}) << ' ';   //true
    cout << lineSegmentIntersection({0.0,2.0}, {2.0,3.0}, {-1.0,5.0}, {2.0,4.0}) << '\n'; //false
    //lineLineIntersection test.
    point p = lineLineIntersection({0.0,2.0}, {2.0,3.0}, {0.0,3.0}, {2.0,0.0});
    cout << '(' << p.x << ',' << p.y << ")\n"; //(0.5,2.25)
    //circumcenter test.
    p = circumcenter({0.0,0.0}, {1.0,3.0}, {4.0,1.0});
    cout << '(' << p.x << ',' << p.y << ")\n"; //(1.86,1.05)
    //lineCircleIntersection test.
    for (point p : lineCircleIntersection({0.0,5.0}, {5.0,1.0}, {1.0,1.0}, 3.0))
        cout << '(' << p.x << ',' << p.y << ") "; //(1.26,3.99) (3.86,1.91)
    cout << '\n';
    for (point p : lineCircleIntersection({0.0,4.0}, {2.0,4.0}, {1.0,1.0}, 3.0))
        cout << '(' << p.x << ',' << p.y << ") "; //(1,4)
    cout << '\n';
    for (point p : lineCircleIntersection({0.0,5.0}, {4.0,4.0}, {1.0,1.0}, 3.0))
        cout << '(' << p.x << ',' << p.y << ") "; //No hay intersecciones.
    cout << '\n';
    //circleCircleIntersection test.
    for (point p : circleCircleIntersection({1.0,1.0}, 3.0, {4.0,3.0}, 2.0))
        cout << '(' << p.x << ',' << p.y << ") "; //(2.15, 3.77) (4, 1)
    cout << '\n';
    for (point p : circleCircleIntersection({1.0,1.0}, 3.0, {-3.0,1.0}, 1.0))
        cout << '(' << p.x << ',' << p.y << ") "; //(-2, 1)
    cout << '\n';
    for (point p : circleCircleIntersection({1.0,1.0}, 3.0, {1.5,1.5}, 2.0))
        cout << '(' << p.x << ',' << p.y << ") "; //No hay intersecciones.
    cout << '\n';
    //pointInPolygon test.
    cout << pointInPolygon({0.0,1.0}, 5, poly1) << ' ';  //1
    cout << pointInPolygon({2.0,0.0}, 5, poly1) << ' ';  //-1
    cout << pointInPolygon({0.5,3.0}, 5, poly1) << '\n'; //0
    cout << pointInPolygon({0.0,1.0}, 5, poly2) << ' ';       //1
    cout << pointInPolygon({2.0,0.0}, 5, poly2) << ' ';       //-1
    cout << pointInPolygon({0.0,11.0/3.0}, 5, poly2) << '\n'; //0
    //areaPolygon test.
    cout << areaPolygon(5, poly1) << ' ';  //-6.5
    cout << areaPolygon(5, poly2) << '\n'; //-11
    //isConvexPolygon test.
    cout << isConvexPolygon(5, poly1) << ' ';  //false
    cout << isConvexPolygon(5, poly2) << '\n'; //true
    return 0;
}