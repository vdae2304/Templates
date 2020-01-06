/*********************************************************************************
* Algoritmo basado en DFS para encontrar un ordenamiendo topologico de un DAG.   *
* Complejidad: O(V + E)                                                          *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define maxv 100000 //Maximo numero de vertices.

int V, E;                //Numero de vertices y aristas.
vector<int> graph[maxv]; //Aristas.

bool cycle;           //Verifica si el grafo tiene ciclos.
vector<int> toposort; //Orden topologico.
int vis[maxv];        //Visitado.

void DFS(int u) {
    if (vis[u] == 1)
        cycle = true;
    else if (!vis[u]) {
        vis[u] = 1;
        for (int v : graph[u])
            DFS(v);
        vis[u] = -1;
        toposort.push_back(u);
    }
}

//Encuentra el orden topologico.
void ToopologicalSort() {
    for (int u = 0; u < V; ++u)
        DFS(u);
    reverse(toposort.begin(), toposort.end());
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> V >> E;
    //Lee la informacion de las aristas.
    for (int i = 0; i < E; ++i) {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
    }
    //Imprime el orden topologico
    ToopologicalSort();
    if (cycle)
        cout << "No es un DAG.";
    else for (int u : toposort)
        cout << u << ' ';
    cout << '\n';
    return 0;
}