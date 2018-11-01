/********************************************************************************
* Algoritmo de Edmonds-Karp para encontrar el maximo flujo en un grafo dirigido *
* Complejidad: O(V * E^2)                                                       *
********************************************************************************/

#include <bits/stdc++.h>
using namespace std;

#define maxn 100000
#define inf 1<<30
typedef pair<int,int> pii;

int V;                  //Numero de vertices
vector<pii> E[maxn];    //Aristas (origen, destino)
map<pii,int> cap, flow; //Capacidad y flujo de las aristas

/*Calcula el flujo maximo de s a t*/
void EdmondsKarp(int s, int t) {
    flow.clear();
    pii pred[maxn];
    do {
        queue<int> Q;
        Q.push(s);
        fill(pred, pred + maxn, pii());

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (pii e : E[u]) {
                if (s != e.second && pred[e.second] == pii() && cap[e] > flow[e]) {
                    pred[e.second] = e;
                    Q.push(e.second);
                }
            }
        }

        if (pred[t] != pii()) {
            int df = inf;
            for (pii e = pred[t]; e != pii(); e = pred[e.first])
                df = min(df, cap[e] - flow[e]);
            for (pii e = pred[t]; e != pii(); e = pred[e.first]) {
                flow[e] += df;
                flow[pii(e.second, e.first)] -= df;
            }
        }
    }
    while (pred[t] != pii());
}

int main() {
    V = 6;
    E[1] = {pii(1,2), pii(1,3)};
    cap[E[1][0]] = 3; cap[E[1][1]] = 3;
    E[2] = {pii(2,3), pii(2,4)};
    cap[E[2][0]] = 2; cap[E[2][1]] = 3;
    E[3] = {pii(3,5)};
    cap[E[3][0]] = 4;
    E[4] = {pii(4,5), pii(4,6)};
    cap[E[4][0]] = 4; cap[E[4][1]] = 2;
    E[5] = {pii(5,6)};
    cap[E[5][0]] = 3;

    EdmondsKarp(1, 6);
    for (int u = 1; u <= V; u++) {
        cout << u << ": ";
        for (pii e : E[u])
            cout << "(" << e.second << ", " << flow[e] << ") ";
        cout << "\n";
    }
    return 0;
}
