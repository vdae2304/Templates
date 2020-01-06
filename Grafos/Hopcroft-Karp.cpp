/*********************************************************************************
* Algoritmo de Hopcroft-Karp para encontrar el emparejamiento maximo en un grafo *
* bipartito.                                                                     *
* Complejodad: O(sqrt(V)*E)                                                      *
*********************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define maxv 100000 //Maximo numero de vertices.

int U, V, E;             //Numero de vertices en cada lado y numero de aristas.
vector<int> graph[maxv]; //Aristas que van de U a V.

int pairU[maxv], pairV[maxv], dist[maxv]; //Pares de vertices en el emparejamiento.

bool BFS() {
    queue<int> Q;
    for (int u = 1; u <= U; ++u) {
        if (!pairU[u]) {
            dist[u] = 0;
            Q.push(u);
        }
        else
            dist[u] = 1e9;
    }
    dist[0] = 1e9;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        if (dist[u] < dist[0]) 
            for (int v : graph[u])
                if (dist[pairV[v]] == 1e9) {
                    dist[pairV[v]] = dist[u] + 1;
                    Q.push(pairV[v]);
                }
    }
    return dist[0] != 1e9;
}

bool DFS(int u) {
    if (!u) 
        return true;
    for (int v : graph[u]) 
        if (dist[pairV[v]] == dist[u] + 1 && DFS(pairV[v])) {
            pairV[v] = u;
            pairU[u] = v;
            return true;
        }
    dist[u] = 1e9;
    return false;
}

//Busca un emparejamiento maximo.
int HopcroftKarp() {
    int size = 0;
    while (BFS()) 
        for (int u = 1; u <= U; ++u) 
            if (!pairU[u] && DFS(u))
                size++;
    return size;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> U >> V >> E;
    //Lee la informacion de las aristas. Los vertices estan indexados en 1.
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    //Imprime la configuracion del emparejamiento.
    cout << "Emparejamiento: " <<  HopcroftKarp() << '\n';
    for (int u = 1; u <= U; ++u)
        if (pairU[u])
            cout << u << " - " << pairU[u] << '\n';
    return 0;
}
