/*********************************************************************************
* Algoritmo de Bellman-Ford para encontrar el camino mas corto desde un veritce. *
* Complejidad: O(VE)                                                             *
*********************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;
#define maxv 100000 //Maximo numero de vertices y aristas.

struct edge {
    int from, to, length; //Origen, destino y longitud.
};

int V, E;         //Numero de vertices y aristas.
edge graph[maxv]; //Aristas.

int s, dist[maxv], pred[maxv]; //Vertice inicial, distancia mas corta y predecesor.

//Encuentra el camino mas corto desde un vertice a todos los demas. 
//Regresa false si existe un ciclo negativo.
bool BellmanFord() {   
    fill_n(dist, V, 1e9);
    fill_n(pred, V, -1);
    dist[s] = 0;
    for (int i = 0; i < V - 1; ++i)
        for (int j = 0; j < E; ++j) { 
            edge e = graph[j];
            if (dist[e.from] != 1e9 && dist[e.from] + e.length < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.length;
                pred[e.to] = e.from;
            }
        }
    for (int j = 0; j < E; ++j) { 
            edge e = graph[j];
            if (dist[e.from] != 1e9 && dist[e.from] + e.length < dist[e.to]) 
                return false;
        }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> V >> E >> s;
    //Lee la informacion de las aristas.
    for (int i = 0; i < 2*E; i += 2) {
        cin >> graph[i].from >> graph[i].to >> graph[i].length;
        graph[i + 1] = edge{graph[i].to, graph[i].from, graph[i].length};
    }
    //Imprime la configuracion.
    E *= 2;
    if (BellmanFord()) 
        for (int i = 0; i < V; ++i)
            cout << i << ": " << pred[i] << ' ' << dist[i] << '\n';
    else
        cout << "Existe un ciclo negativo.\n";
    return 0;
}
