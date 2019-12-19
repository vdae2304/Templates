/*********************************************************************************
* Algoritmo de Aho Corasick para encontrar todas las ocurrencias de una lista de *
* patrones en un texto.                                                          *
* Complejidad: O(len(texto) + len(patrones) + num ocurrencias)                   *
*********************************************************************************/

#include <iostream>
using namespace std;

#define maxc 26     //Longitud del alfabeto.
#define maxn 100    //Maximo numero de patrones.
#define maxs 100000 //Maximo numero de nodos.

int n;                      //Numero de patrones.
string text, pattern[maxn]; //Texto y lista de patrones.

int nnodes;           //Numero de nodos.
struct node {
    node *nxt[maxc];  //Nodo siguiente en el Trie.
    node *link;       //Sufijo propio mas largo que es prefijo de un patron.
    bool isEnd[maxn]; //Es nodo terminal de algun patron.
} Trie[maxs];

//Retorna el nodo siguiente.
node *nextNode(node *curr, char c) {
    if (curr == NULL)
        return Trie;
    if (curr->nxt[c] == NULL)
        return nextNode(curr->link, c);
    return curr->nxt[c];
}

//Construye los links de cada nodo.
void buildLink(node *curr) {
    for (char c = 0; c < maxc; ++c) {
        node *nxt = curr->nxt[c];
        if (nxt != NULL) {
            nxt->link = nextNode(curr->link, c);
            for (int i = 0; i < n; ++i)
                if (nxt->link->isEnd[i])
                    nxt->isEnd[i] = true;
            buildLink(nxt);
        }
    }
}

//Construye el Trie de patrones.
void buildTrie() {
    for (int i = 0; i < n; ++i) {
        node *curr = Trie;
        for (int j = 0; j < pattern[i].size(); ++j) {
            char c = pattern[i][j] - 'a';
            if (curr->nxt[c] == NULL)
                curr->nxt[c] = Trie + (++nnodes);
            curr = curr->nxt[c];
        }
        curr->isEnd[i] = true;
    }
    buildLink(Trie);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    
    //Lee el texto y los patrones.
    getline(cin, text);
    cin >> n;
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
