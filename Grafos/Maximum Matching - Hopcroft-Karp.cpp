/***************************************************************************
* Algoritmo de Hopcroft-Karp para encontrar el emparejamiento maximo en un *
* grafo bipartito.                                                         *
* Complejodad: O(sqrt(V)*E)                                                *
***************************************************************************/

#include <iostream>
#include <queue>
using namespace std;
#define maxn 100000
#define inf 1<<30

int U, V;            //Numero de vertices (indexeados en 1) en ambos lados
vector<int> E[maxn]; //Aristas que van de U a V
int pairU[maxn], pairV[maxn], dist[maxn]; //Pares de vertices en el emparejamiento

/*Verifica si existe un camino de aumento, i.e. alternante y extremos libres*/
bool BFS() {
    queue<int> Q;
    for (int u = 1; u <= U; u++) {
        if (!pairU[u]) {
            dist[u] = 0;
            Q.push(u);
        }
        else
            dist[u] = inf;
    }
    dist[0] = inf;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        if (dist[u] < dist[0]) {
            for (int v : E[u]) {
                if (dist[pairV[v]] == inf) {
                    dist[pairV[v]] = dist[u] + 1;
                    Q.push(pairV[v]);
                }
            }
        }
    }
    return (dist[0] != inf);
}

/*Verifica si existe un camino de aumento que comience en u*/
bool DFS(int u) {
    if (u) {
        for (int v : E[u]) {
            if (dist[pairV[v]] == dist[u] + 1 && DFS(pairV[v])) {
                pairV[v] = u;
                pairU[u] = v;
                return true;
            }
        }
        dist[u] = inf;
        return false;
    }
    return true;
}

/*Busca el emparejamiento maximo y retorna su tamaño*/
int HopcroftKarp() {
    int size = 0;
    while (BFS()) {
        for (int u = 1; u <= U; u++) {
            if (!pairU[u] && DFS(u))
                size++;
        }
    }
    return size;
}

int main() {
    U = 6; V = 6;
    E[1] = {2, 3};
    E[3] = {1, 4};
    E[4] = {2};
    E[5] = {3, 4};
    E[6] = {6};
    cout << HopcroftKarp() << "\n";
    for (int u = 1; u <= U; u++)
        cout << u << " -> " << pairU[u] << "\n";
    return 0;
}
