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

vector<vector<int>> SCC; //Componentes fuertemente conexas.

int idx[maxn], low[maxn], lst_id; //Indices, ultimo indice.
stack<int> S;                     //Vertices pendientes.
bool onStack[maxn];               //Esta en la pila.

//Encuentra la componente fuertemente conexa de u.
void StrongConnect(int u) {
    idx[u] = ++lst_id;
    low[u] = lst_id;
    S.push(u);
    onStack[u] = true;

    for (int v : graph[u]) {
        if(!idx[v]) {
            StrongConnect(v);
            low[u] = min(low[u], low[v]);
        }
        else if (onStack[v]) 
            low[u] = min(low[u], idx[v]);
    }

    if (low[u] == idx[u]) {
        SCC.push_back(vector<int>());
        while (S.top() != u) {
            onStack[S.top()] = false;
            SCC.back().push_back(S.top());
            S.pop();
        }

        onStack[u] = false;
        SCC.back().push_back(u);
        S.pop();
    }
}

//Algoritmo de Tarjan para encontrar las componentes fuertemente conexas.
void Tarjan() {
    for (int u = 0; u < V; ++u)
        if (!idx[u])
            StrongConnect(u);
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

    //Imprime las componentes fuertemente conexas.
    Tarjan();
    for (int i = 0; i < SCC.size(); ++i) {
        for (int u : SCC[i])
            cout << u << ' ';
        cout << '\n';
    }

    return 0;
}