#include <bits/stdc++.h>
using namespace std;

/***********************************************
* Kuhn's algorithm for maximum bipartite match *
* Time Complexity: O(VE)                       *
***********************************************/

#define MAXV 100000

int L, R;
vector<int> E[MAXV];
int match[MAXV], vis[MAXV];

//Finds an augmenting path that ends in u
bool DFS(int u) {
    if (vis[u])
        return false;
    vis[u] = true;
    for (int v : E[u])
        if (match[v] == -1 || DFS(match[v])) {
            match[v] = u;
            return true;
        }
    return false;
}

//Finds maximal matching
void Kuhn() {
    memset(match, -1, sizeof match);
    for (int i = 0; i < L; i++) {
        memset(vis, false, sizeof vis);
        DFS(i);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> L >> R;

    for (int i = 0, j, M; i < L; i++) {
        cin >> M;
        while (M--) {
            cin >> j;
            E[i].push_back(j);
        }
    }

    Kuhn();
    for (int i = 0; i < R; i++)
        cout << "\n" << match[i] << " " << i;
    return 0;
}
