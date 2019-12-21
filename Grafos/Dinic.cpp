/*********************************************************************************
* Algoritmo de Dinic para encontrar el maximo flujo en un grafo dirigido.        *
* Complejidad: O(E * V^2)                                                        *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define maxn 100000 //Maximo numero de vertices.
typedef int T;      //Tipo de dato del flujo.

struct edge {
    int to;           //Destino.
    T capacity, flow; //Capacidad, flujo.
    int rev;          //Arista invertida.
};

int V, E;                 //Numero de vertices y aristas.
vector<edge> graph[maxn]; //Aristas.

int s, t;                   //Fuente y sumidero.
int level[maxn], ptr[maxn]; //Distancia a s y numero de aristas visitadas.

//Verifica si se puede enviar flujo de s a t.
bool BFS() {
    queue<int> Q;
    Q.push(s);

    fill_n(level, V, -1);
    level[s] = 0;

    while (!Q.empty()) {
        int curr = Q.front();
        Q.pop();
        for (edge e : graph[curr]) 
            if (level[e.to] == -1 && e.flow < e.capacity) {
                level[e.to] = level[curr] + 1;
                Q.push(e.to);
            }
    }

    return level[t] != -1;
}

//Envia flujo de s a t.
T DFS(int curr, T flow) {
    if (curr == t)
        return flow;

    for (; ptr[curr] < graph[curr].size(); ++ptr[curr]) {
        edge &e = graph[curr][ptr[curr]];

        if (level[e.to] == level[curr] + 1 && e.flow < e.capacity) {
            T currflow = DFS(e.to, min(flow, e.capacity - e.flow));
            if (currflow > 0) {
                e.flow += currflow;
                graph[e.to][e.rev].flow -= currflow;
                return currflow;
            }
        }
    }

    return 0;
}

//Calcula el maximo flujo de s a t. 
T Dinic() {
    T flow = 0, currflow;
    while (BFS()) {
        fill_n(ptr, V, 0);
        do {
            currflow = DFS(s, 1e9);
            flow += currflow;
        }
        while (currflow > 0);
    }
    return flow;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> V >> E >> s >> t;

    //Lee la informacion de las aristas.
    for (int i = 0; i < E; ++i) {
        int from, to; 
        T capacity;
        cin >> from >> to >> capacity;

        graph[from].push_back(edge {to, capacity, 0, (int)graph[to].size()});
        graph[to].push_back(edge {from, 0, 0, (int)graph[from].size() - 1});
    }

    //Imprime la configuracion del flujo.
    cout << "Flujo maximo: " << Dinic() << '\n';
    for (int i = 0; i < V; ++i)
        for (edge e : graph[i]) 
            if (e.capacity > 0)
                cout << i << ' ' << e.to << ": " << e.flow << '/' << e.capacity << '\n';

    return 0;
}
