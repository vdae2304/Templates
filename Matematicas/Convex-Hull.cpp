/*********************************************************************************
* Algoritmo de Graham-Scan para encontrar la envolvente conexa de un poligono.   *
* Complejidad: O(n log n)                                                        *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
#define maxn 100000 //Maximo numero de puntos.

typedef pair<int, int> point;
#define x first
#define y second

point operator - (const point &v, const point &w) {
    return point(v.x - w.x, v.y - w.y);
}

int cross(const point &v, const point &w) {
    return v.x * w.y - v.y * w.x;
}

int n;              //Numero de puntos.
point P[maxn];      //Lista de puntos.
vector<point> hull; //Envolvente conexa.

//Compara con respecto al angulo formado con P[0].
bool compareByAngle(const point &v, const point &w) {
    return cross(v - P[0], w - P[0]) > 0;
}

//Algoritmo de Graham-Scan para encontrar la envolvente conexa.
void GrahamScan() {
    int leftbottom = min_element(P, P + n) - P;
    swap(P[0], P[leftbottom]);
    sort(P, P + n, compareByAngle);
    for (int i = 0; i < n; ++i) {
        while (hull.size() > 1 && cross(hull[hull.size() - 1] - hull[hull.size() - 2], P[i] - hull[hull.size() - 2]) < 0)
            hull.pop_back();
        hull.push_back(P[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    //Lee los puntos.
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> P[i].x >> P[i].y;
    //Imprime la envolvente convexa.
    GrahamScan();
    for (int i = 0; i < hull.size(); ++i)
        cout << '(' << hull[i].x << ", " << hull[i].y << ")\n";
    return 0;
}