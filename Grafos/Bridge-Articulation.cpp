/*********************************************************************************
* Algoritmo de Tarjan para encontrar puentes y puntos de articulacion.           *
* Complejidad: O(V + E)                                                          *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

#define maxn 100000 //Maximo numero de vertices.

int V, E;                //Numero de vertices y aristas.
vector<int> graph[maxn]; //Aristas.

bool artpoint[maxn];           //Puntos de articulacion
vector<pair<int, int>> bridge; //Puentes

int idx[maxn], low[maxn], lst_id; //Indices, ultimo indice.

//Enumera los vertices con una DFS.
void DFS(int u, int pred) {
    idx[u] = ++lst_id;
    low[u] = lst_id;
    int children = 0;

    for (int v : graph[u]) {
        if(!idx[v]) {
            children++;
            DFS(v, u);
            low[u] = min(low[u], low[v]);

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
    for (int u = 0; u < V; ++u)
        if (!idx[u])
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