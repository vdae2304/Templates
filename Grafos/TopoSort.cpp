/*********************************************************************************
* Algoritmo para encontrar un ordenamiendo topologico de un DAG.                 *
* Complejidad: O(V + E)                                                   *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define maxn 100000 //Maximo numero de vertices.

int V, E;                //Numero de vertices y aristas.
vector<int> graph[maxn]; //Aristas.

bool cycle;         //Verifica que no haya ciclos.
vector<int> sorted; //Orden topologico.
int vis[maxn];      //Visitado.

//Encuentra el orden topologico iniciando en un vertice dado.
void DFS(int u) {
    if (vis[u] == 1) {
        cycle = true;
        return;
    }
    else if (!vis[u]) {
        vis[u] = 1;
        for (int v : graph[u])
            DFS(v);
        vis[u] = -1;
        sorted.push_back(u);
    }
}

//Encuentra el orden topologico.
void ToopologicalSort() {
    for (int u = 0; u < V; ++u)
        if (!vis[u])
            DFS(u);
    reverse(sorted.begin(), sorted.end());
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
        cout << "No es un DAG.\n";
    else {
        for (int u : sorted)
            cout << u << ' ';
        cout << '\n';
    }

    return 0;
}