/*********************************************************************************
* Algoritmo de Dinic para encontrar el flujo maximo en un grafo dirigido.        *
* Complejidad: O(E * V^2)                                                        *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define maxv 100000 //Maximo numero de vertices.

struct edge {
    int to, rev;        //Destino, arista invertida.
    int flow, capacity; //Flujo, capacidad.
};

int V, E;                 //Numero de vertices y aristas.
vector<edge> graph[maxv]; //Aristas.

int s, t;                   //Fuente y sumidero.
int level[maxv], ptr[maxv]; //Distancia desde s y numero de aristas visitadas.

//Verifica si se puede enviar flujo de s a t.
bool BFS() {
    fill_n(level, V, -1);
    level[s] = 0;
    queue<int> Q;
    Q.push(s);
    while (!Q.empty() && level[t] == -1) {
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
int DFS(int curr, int flow) {
    if (curr == t || !flow)
        return flow;
    for (int &i = ptr[curr]; i < graph[curr].size(); ++i) {
        edge &e = graph[curr][i];
        if (level[e.to] == level[curr] + 1)
            if (int currflow = DFS(e.to, min(flow, e.capacity - e.flow))) {
                e.flow += currflow;
                graph[e.to][e.rev].flow -= currflow;
                return currflow;
            }
    }
    return 0;
}

//Calcula el flujo maximo de s a t.
int Dinic() {
    int flow = 0;
    while (BFS()) {
        fill_n(ptr, V, 0);
        while (int currflow = DFS(s, 1e9))
            flow += currflow;
    }
    return flow;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> V >> E >> s >> t;
    //Lee la informacion de las aristas.
    for (int i = 0; i < E; ++i) {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        graph[from].push_back(edge{to, (int)graph[to].size(), 0, capacity});
        graph[to].push_back(edge{from, (int)graph[from].size() - 1, 0, 0});
    }
    //Imprime la configuracion del flujo.
    cout << "Flujo maximo: " << Dinic() << '\n';
    for (int i = 0; i < V; ++i)
        for (edge e : graph[i]) 
            if (e.capacity)
                cout << i << ' ' << e.to << ": " << e.flow << '/' << e.capacity << '\n';
    return 0;
}
