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
#define weight first.first
#define from   first.second
#define to     second

int V, M, W;
pii E[MAXV];
int parent[MAXV], Rank[MAXV];

//Union-Find by Rank and Path Compression
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
        if (Rank[b] < Rank[a])
            parent[b] = a;
        else if (Rank[a] < Rank[b])
            parent[a] = b;
        else {
            parent[b] = a;
            Rank[a]++;
        }
        return true;
    }
}

void InitUnionFind() {
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        Rank[i] = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> V >> M;

    for (int i = 0; i < M; i++)
        cin >> E[i].u >> E[i].v >> E[i].d;
    sort(E, E + M);

    InitUnionFind();
    for (int i = 0; i < M; i++)
        if (Union(E[i].u, E[i].v)) {
            W += E[i].d;
            cout << "\n" << E[i].u << " " << E[i].v << " " << E[i].d;
        }
    cout << "\nTotal weight: " << W;
    return 0;
}
