/*********************************************************************************
* Algoritmo de Aho Corasick para encontrar todas las ocurrencias de una lista de *
* patrones en un texto.                                                          *
* Complejidad: O(len(texto) + len(patrones) + num ocurrencias)                   *
*********************************************************************************/

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define maxc 26     //Longitud del alfabeto.
#define maxn 100    //Maximo numero de patrones.
#define maxs 100000 //Maximo numero de nodos.

int n;                      //Numero de patrones.
string text, pattern[maxn]; //Texto y lista de patrones.

int nnodes;                 //Numero de nodos.
struct node {
    node *nxt[maxc], *link; //Nodos adyacentes y mayor sufijo que es prefijo en el Trie.
    bool isEnd[maxn];       //Es nodo terminal de algun patron.
} Trie[maxs];               //Nodos del Trie.

node *nextNode(node *curr, char c) {
    if (!curr)
        return Trie;
    if (!curr->nxt[c])
        return nextNode(curr->link, c);
    return curr->nxt[c];
}

//Construye los links de cada nodo.
void buildLink() {
    queue<node*> Q;
    Q.push(Trie);
    while (!Q.empty()) {
        node *curr = Q.front();
        Q.pop();
        for (char c = 0; c < maxc; ++c)
            if (node *nxt = curr->nxt[c]) {
                nxt->link = nextNode(curr->link, c);
                for (int i = 0; i < n; ++i)
                    if (nxt->link->isEnd[i])
                        nxt->isEnd[i] = true;
                Q.push(nxt);
            }
    }
}

//Construye el Trie de patrones.
void buildTrie() {
    nnodes = 0;
    memset(Trie, 0, sizeof(Trie));
    for (int i = 0; i < n; ++i) {
        node *curr = Trie;
        for (char c : pattern[i]) {
            if (!curr->nxt[c - 'a'])
                curr->nxt[c - 'a'] = Trie + (++nnodes);
            curr = curr->nxt[c - 'a'];
        }
        curr->isEnd[i] = true;
    }
    buildLink();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    //Lee el texto y los patrones.
    cin >> text >> n;
    for (int i = 0; i < n; ++i)
        cin >> pattern[i];
    buildTrie();
    //Imprime todas las ocurrencias.
    node *curr = Trie;
    for (int i = 0; i < text.size(); ++i) { 
        curr = nextNode(curr, text[i] - 'a');
        for (int j = 0; j < n; ++j)
            if (curr->isEnd[j])
                cout << pattern[j] << " aparece en la posicion " << i - pattern[j].size() + 1 << '\n';
    }
    return 0;
}
