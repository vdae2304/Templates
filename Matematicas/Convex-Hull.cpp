/*********************************************************************************
* Algoritmo de Graham-Scan para encontrar la envolvente convexa de un poligono.  *
* Complejidad: O(n log n)                                                        *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
using namespace std;
#define maxn 100000 //Maximo numero de puntos.

typedef complex<int> point;
#define x real()
#define y imag()

int n;              //Numero de puntos.
point P[maxn];      //Lista de puntos.
vector<point> hull; //Envolvente convexa.

//Compara usando el producto cruz quien posee el menor angulo con centro en P[0].
bool compareByAngle(const point &v, const point &w) {
    return (conj(v - P[0]) * (w - P[0])).y > 0;
}

//Algoritmo de Graham-Scan para encontrar la envolvente convexa.
void GrahamScan() {
    int first = 0;
    for (int i = 1; i < n; ++i)
        if (P[i].y < P[first].y || (P[i].y == P[first].y && P[i].x < P[first].x))
            first = i;
    swap(P[0], P[first]);
    sort(P, P + n, compareByAngle);
    hull.clear();
    for (int i = 0; i < n; ++i) {
        while (hull.size() > 1 && (conj(hull[hull.size()-1] - hull[hull.size()-2]) * 
               (P[i] - hull[hull.size()-2])).y < 0)
            hull.pop_back();
        hull.push_back(P[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    //Lee los puntos.
    cin >> n;
    for (int i = 0; i < n; ++i) {
    	int px, py;
        cin >> px >> py;
        P[i] = point(px, py);
    }
    //Imprime la envolvente convexa.
    GrahamScan();
    for (int i = 0; i < hull.size(); ++i)
        cout << '(' << hull[i].x << ", " << hull[i].y << ")\n";
    return 0;
}