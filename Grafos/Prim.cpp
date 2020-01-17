/*********************************************************************************
* Algoritmo de Prim para encontrar el arbol de expansion minima.                 *
* Complejidad: O((E + V)log V)                                                   *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define maxv 100000 //Maximo numero de vertices.

typedef pair<int, int> edge;
#define length first
#define to     second

int V, E;                 //Numero de vertices y aristas.
vector<edge> graph[maxv]; //Aristas.

int dist[maxv], pred[maxv]; //Distancia al arbol y padre en el arbol.

//Encuentra el arbol de expansion minima.
int Prim() {
    int cost = 0;
    fill_n(dist, V, 1e9);
    fill_n(pred, V, -1);
    dist[0] = 0;
    priority_queue<edge> pq;
    pq.push(edge(dist[0], 0));
    while (!pq.empty()) {
        int curr = pq.top().to, dcurr = -pq.top().length;
        pq.pop();
        if (dist[curr] != dcurr)
            continue;
        cost += dcurr;
        for (edge e : graph[curr]) 
            if (e.length < dist[e.to]) {
                dist[e.to] = e.length;
                pred[e.to] = curr;
                pq.push(edge(-dist[e.to], e.to));
            }
    }
    return cost;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> V >> E;
    //Lee la informacion de las aristas.
    for (int i = 0; i < E; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].push_back(edge(d, v));
        graph[v].push_back(edge(d, u));
    }
    //Imprime la configuracion.
    cout << "Peso total: " << Prim() << '\n';
    for (int i = 0; i < V; ++i)
        cout << pred[i] << ' ' << i << ' ' << dist[i] << '\n';
    return 0;
}
