/*********************************************************************************
* Algoritmo de Dijktra para encontrar el camino mas corto desde un veritce.      *
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

int s, dist[maxv], pred[maxv]; //Vertice inicial, distancia mas corta y predecesor.

//Encuentra el camino mas corto desde un vertice a todos los demas.
void Dijkstra() {   
    fill_n(dist, V, 1e9);
    fill_n(pred, V, -1);
    dist[s] = 0;
    priority_queue<edge> pq;
    pq.push(edge(dist[s], s));
    while (!pq.empty()) {
        int curr = pq.top().to, dcurr = -pq.top().length;
        pq.pop();
        if (dist[curr] != dcurr)
            continue;
        for (edge e : graph[curr]) 
            if (dist[curr] + e.length < dist[e.to]) {
                dist[e.to] = dist[curr] + e.length;
                pred[e.to] = curr;
                pq.push(edge(-dist[e.to], e.to));
            }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> V >> E >> s;
    //Lee la informacion de las aristas.
    for (int i = 0; i < E; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].push_back(edge(d, v));
        graph[v].push_back(edge(d, u));
    }
    //Imprime la configuracion.
    Dijkstra();
    for (int i = 0; i < V; ++i)
        cout << i << ": " << pred[i] << ' ' << dist[i] << '\n';
    return 0;
}
