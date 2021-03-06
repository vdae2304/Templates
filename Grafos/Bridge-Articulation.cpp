/*********************************************************************************
* Algoritmo de Tarjan para encontrar puentes y puntos de articulacion.           *
* Complejidad: O(V + E)                                                          *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
#define maxv 100000 //Maximo numero de vertices.

int V, E;                //Numero de vertices y aristas.
vector<int> graph[maxv]; //Aristas.

bool artpoint[maxv];              //Puntos de articulacion.
vector<pair<int, int>> bridge;    //Puentes.
int lst_id, idx[maxv], low[maxv]; //Indice de los vertices, menor vertice alcanzable.

void DFS(int u, int pred) {
    idx[u] = low[u] = lst_id++;
    int children = 0;
    for (int v : graph[u]) {
        if(idx[v] == -1) {
            DFS(v, u);
            low[u] = min(low[u], low[v]);
            children++;
            if ((pred == -1 && children > 1) || (pred != -1 && low[v] >= idx[u]))
                artpoint[u] = true;
            if (low[v] > idx[u])
                bridge.push_back(make_pair(u, v));
        }
        else if (v != pred)
            low[u] = min(low[u], idx[v]);
    }
}

//Algoritmo de Tarjan.
void Tarjan() {
    lst_id = 0;
    fill_n(artpoint, V, false);
    bridge.clear();
    fill_n(idx, V, -1);
    for (int u = 0; u < V; ++u)
        if (idx[u] == -1)
            DFS(u, -1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> V >> E;
    //Lee la informacion de las aristas.
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    //Imprime los puentes y puntos de articulacion.
    Tarjan();
    cout << "Puntos de articulacion:\n";
    for (int i = 0; i < V; ++i)
        if (artpoint[i])
            cout << i << ' ';
    cout << "\nPuentes:\n";
    for (int i = 0; i < bridge.size(); ++i)
        cout << bridge[i].first << ' ' << bridge[i].second << '\n';
    return 0;
}