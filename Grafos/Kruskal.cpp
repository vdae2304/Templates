/*********************************************************************************
* Algoritmo de Kruskal para encontrar el arbol de expansion minima.              *
* Complejidad: O(E log V)                                                        *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
#define maxv 100000 //Maximo numero de vertices y aristas.

typedef pair<int, pair<int, int>> edge;
#define weight first
#define from   second.first
#define to     second.second

int V, E;         //Numero de vertices y aristas.
edge graph[maxv]; //Aristas.

int parent[maxv], Rank[maxv]; //Union-Find por rango y compresion de camino.
vector<int> MST;              //Arbol de expansion minima.

int Find(int x) {
    if (parent[x] != x)
        parent[x] = Find(parent[x]);
    return parent[x];
}

void Union(int x, int y) {
    if (Rank[x] < Rank[y])
        parent[x] = y;
    else {
        parent[y] = x;
        if (Rank[x] == Rank[y])
            Rank[x]++;
    }
}

//Encuentra el arbol de expansion minima.
int Kruskal() {
    int cost = 0;
    MST.clear();
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
        Rank[i] = 0;
    }
    sort(graph, graph + E);
    for (int i = 0; i < E; ++i)
        if (Find(graph[i].from) != Find(graph[i].to)) {
            cost += graph[i].weight;
            Union(Find(graph[i].from), Find(graph[i].to));
            MST.push_back(i);
        }
    return cost;
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
