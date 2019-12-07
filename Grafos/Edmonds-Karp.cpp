/*********************************************************************************
* Algoritmo de Edmonds-Karp para encontrar el maximo flujo en un grafo dirigido. *
* Complejidad: O(V * E^2) y O(E * maxflujo)                                      *
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
	edge *rev;        //Arista invertida.

	edge(int _to, T _capacity, T _flow, edge *_rev) {
		to = _to; capacity = _capacity; flow = _flow; rev = _rev;
	}
};

int V, E;                  //Numero de vertices y aristas.
vector<edge*> graph[maxn]; //Aristas.

//Calcula el flujo maximo de s a t. 
T EdmondsKarp(int s, int t) {
    T flow = 0;
    edge *pred[maxn];

    do {
    	//Realiza una BFS desde s hasta t.
        queue<int> Q;
        Q.push(s);
        fill(pred, pred + V, nullptr);

        while (!Q.empty()) {
            int curr = Q.front();
            Q.pop();
            for (edge *e : graph[curr])
                if (pred[e->to] == nullptr && e->to != s && e->capacity > e->flow) {
                    pred[e->to] = e;
                    Q.push(e->to);
                }
        }

        //Encontramos un camino de aumento.
        if (pred[t] != nullptr) {
            T df = 1e9;
            for (edge *e = pred[t]; e != nullptr; e = pred[e->rev->to])
                df = min(df, e->capacity - e->flow);
            for (edge *e = pred[t]; e != nullptr; e = pred[e->rev->to]) {
                e->flow += df;
                e->rev->flow -= df;
            }
            flow += df;
        }
    }
    while (pred[t] != nullptr);

    return flow;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> V >> E;

    //Lee la informacion de las aristas.
    for (int i = 0; i < E; i++) {
    	int from, to; 
    	T capacity;
    	cin >> from >> to >> capacity;

    	graph[from].push_back(new edge(to, capacity, 0, nullptr));
    	graph[to].push_back(new edge(from, 0, 0, graph[from].back()));
    	graph[from].back()->rev = graph[to].back();
    }

    cout << "Flujo maximo: " << EdmondsKarp(0, V - 1) << '\n';

    //Imprime la configuracion del flujo.
    for (int i = 0; i < V; i++)
    	for (edge *e : graph[i]) {
    		if (e->capacity > 0)
    			cout << i << ' ' << e->to << ": " << e->flow << '/' << e->capacity <<'\n';
    		delete e;
    	}

    return 0;
}
