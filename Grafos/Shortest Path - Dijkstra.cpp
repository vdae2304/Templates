#include <bits/stdc++.h>
using namespace std;

/*******************************************
* Dijktra's algorithm for shortest path    *
* Time Complexity: O(E log V)              *
*******************************************/

#define MAXV 100000
typedef pair<pair<int, int>, int> pii;
#define mp(a,b,c) make_pair(make_pair(a,b),c)

#define d first.first
#define u first.second
#define p second

int V;
vector<pii> E[MAXV];
int dist[MAXV], parent[MAXV];

//Find shortest path from source to all vertices
void Dijkstra(int source) {
    priority_queue<pii> pq;
    pq.push(mp(0, source, -1));
    memset(dist, -1, sizeof dist);
    memset(parent, -1, sizeof parent);

    while (!pq.empty()) {
        pii t = pq.top();
        pq.pop();

        if (dist[t.u] != -1)
            continue;
        dist[t.u] = -t.d;
        parent[t.u] = t.p;

        for (pii nxt : E[t.u])
            if (dist[nxt.u] == -1)
                pq.push(mp(t.d - nxt.d, nxt.u, t.u));
    }
}

//Print shortest path from source to destiny
void PrintPath(int source, int destiny) {
    Dijkstra(destiny);
    for (; source != -1; source = parent[source])
        cout << source << " ";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    int M, a, b, w;
    cin >> V >> M;

    while (M--) {
        cin >> a >> b >> w;
        E[a].push_back(mp(w, b, 0));
        E[b].push_back(mp(w, a, 0));
    }

    cin >> a >> b;
    PrintPath(a, b);
    return 0;
}
