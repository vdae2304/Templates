/*********************************************************************************
* Algoritmo de Kosaraju para encontrar las componentes fuertemente conexas.      *
* Complejidad: O(V + E)                                                          *
*********************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;
#define maxv 100000 //Maximo numero de vertices.

int V, E;                                 //Numero de vertices y aristas.
vector<int> graph[maxv], transpose[maxv]; //Aristas y aristas transpuestas.

int component[maxv]; //Componentes fuertemente conexas.
stack<int> S;        //Vertices pendientes.
bool vis[maxv];      //Visitado.

void DFS(int u) {
    if (!vis[u]) {
        component[u] = -1;
        vis[u] = true;
        for (int v : graph[u]) 
            DFS(v);
        S.push(u);
    }
}

void Assign(int u, int root) {
    if (component[u] == -1) {
        component[u] = root;
        for (int v : transpose[u])
            Assign(v, root);
    }
}

//Algoritmo de Kosaraju para encontrar las componentes fuertemente conexas.
void Kosaraju() {
    for (int u = 0; u < V; ++u)
        DFS(u);
    while (!S.empty()) {
        Assign(S.top(), S.top());
        S.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> V >> E;
    //Lee la informacion de las aristas.
    for (int i = 0; i < E; ++i) {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
        transpose[to].push_back(from);
    }
    //Imprime las componentes fuertemente conexas.
    Kosaraju();
    for (int i = 0; i < V; ++i)
        cout << i << ": " << component[i] << '\n';
    return 0;
}