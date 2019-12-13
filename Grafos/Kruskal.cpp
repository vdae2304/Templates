/*********************************************************************************
* Algoritmo de Kruskal para encontrar el arbol de expansion minima.              *
* Complejidad: O(E log V)                                                        *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

#define maxn 100000 //Maximo numero de vertices.

typedef pair<int, pair<int, int> > edge;
#define weight first
#define from   second.first
#define to     second.second

int V, E;         //Numero de vertices y aristas.
edge graph[maxn]; //Aristas.

int parent[maxn], Rank[maxn]; //Union-Find por rango y compresion de camino.
vector<int> MST;              //Arbol de expansion minima.

int Find(int x) {
    if (parent[x] != x)
        parent[x] = Find(parent[x]);
    return parent[x];
}

bool Union(int x, int y) {
    int a = Find(x), b = Find(y);
    if (a == b)
        return false;
    else {
        if (Rank[a] < Rank[b])
            parent[a] = b;
        else {
            parent[b] = a;
            if (Rank[a] == Rank[b])
                Rank[a]++;
        }
        return true;
    }
}

//Encuentra el arbol de expansion minima.
int Kruskal() {
    int W = 0;
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
        Rank[i] = 0;
    }

    sort(graph, graph + E);
    for (int i = 0; i < E; ++i)
        if (Union(graph[i].from, graph[i].to)) {
            W += graph[i].weight;
            MST.push_back(i);
        }
    return W;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> V >> E;

    //Lee la informacion de las aristas.
    for (int i = 0; i < E; ++i)
        cin >> graph[i].from >> graph[i].to >> graph[i].weight;

    //Imprime la configuracion del arbol de expansion minima.
    cout << "Peso total: " << Kruskal() << '\n';
    for (int i : MST)
        cout << graph[i].from << ' ' << graph[i].to << ' ' << graph[i].weight << '\n';
    return 0;
}
