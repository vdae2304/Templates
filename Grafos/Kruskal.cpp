#include <bits/stdc++.h>
using namespace std;

/*************************************************
* Kruskal's algorithm for minimal spanning tree  *
* Time Complexity: O(E log V)                    *
*************************************************/

#define MAXV 100000
typedef pair<pair<int, int>, int> pii;

#define d first.first
#define u first.second
#define v second

int V, M;
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
        if (Union(E[i].u, E[i].v))
            cout << "\n" << E[i].u << " " << E[i].v << " " << E[i].d;
    return 0;
}
