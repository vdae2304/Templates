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

int vis[maxv];        //Visitados.
vector<int> toposort; //Orden topologico.

bool DFS(int u) {
    vis[u] = 1;
    for (int v : graph[u])
        if (vis[v] == 1 || (!vis[v] && !DFS(v)))
            return false;
    vis[u] = -1;
    toposort.push_back(u);
    return true;
}

//Encuentra el orden topologico. Regresa false si no existe.
bool TopologicalSort() {
    toposort.clear();
    fill_n(vis, V, false);
    for (int u = 0; u < V; ++u)
        if (vis[u] == 1 || (!vis[u] && !DFS(u)))
            return false;
    reverse(toposort.begin(), toposort.end());
    return true;
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
    if (!TopologicalSort())
        cout << "El grafo tiene ciclos.";
    else for (int u : toposort)
        cout << u << ' ';
    cout << '\n';
    return 0;
}