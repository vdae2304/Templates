/*********************************************************************************
* Algoritmo de Tarjan para encontrar las componentes fuertemente conexas.        *
* Complejidad: O(V + E)                                                          *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

#define maxn 100000 //Maximo numero de vertices.

int V, E;                //Numero de vertices y aristas.
vector<int> graph[maxn]; //Aristas.

int idx[maxn], low[ind], lst_id; //Indices, ultimo indice.
stack<int> S;                    //Vertices pendientes.
bool vis[maxn];                  //Visitado.

//Encuentra la componente fuertemente conexa de u.
void StrongConnect(int u) {
    idx[u] = ++lst_id;
    low[u] = lst_id;
    S.push(u);
    vis[u] = true;

    for (int v : graph[u]) {
        if(!idx[v]) {
            StrongConnect(v);
            low[u] = min(low[u], low[v]);
        }
        else if (vis[v]) 
            low[u] = min(low[u], idx[v]);
    }

    if (low[u] == idx[u]) {
        ;
    }
}

//Algoritmo de Tarjan para encontrar las componentes fuertemente conexas.
void Tarjan() {
    for (int u = 0; u < V; ++v)
        if (!vis[u])
            StrongConnect(u);
}

int main() {
    return 0;
}