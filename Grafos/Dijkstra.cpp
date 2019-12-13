/*********************************************************************************
* Algoritmo de Dijktra para encontrar el camino mas corto.                       *
* Complejidad: O((E + V)log V)                                                   *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

#define maxn 100000 //Maximo numero de vertices.

typedef pair<int, int> edge;
#define length first
#define to     second

int V, E;                 //Numero de vertices y aristas.
vector<edge> graph[maxn]; //Aristas.

int s;                      //Vertice inicial.
int dist[maxn], pred[maxn]; //Distancia desde s y predecesor en el camino.
bool vis[maxn];             //Visitado.

//Encuentra el camino mas corto desde un vertice a todos los demas.
void Dijkstra() {   
    fill_n(dist, V, 1e9);
    fill_n(pred, V, -1);
    fill_n(vis, V, false);
    dist[s] = 0;

    priority_queue<edge> pq;
    pq.push(edge(dist[s], s));

    while (!pq.empty()) {
        int curr = pq.top().to;
        pq.pop();
        vis[curr] = true;

        for (edge e : graph[curr]) 
            if (!vis[e.to] && dist[curr] + e.length < dist[e.to]) {
                dist[e.to] = dist[curr] + e.length;
                pred[e.to] = curr;
                pq.push(edge(-dist[e.to], e.to));
            }
    }
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
    cin >> s;
    Dijkstra();
    for (int i = 0; i < V; ++i)
        cout << i << ": " << pred[i] << ' ' << dist[i] << '\n';

    return 0;
}
