/************************************************************************
* Algoritmo de Aho Corasick para encontrar todas las ocurrencias de una *
* lista de palabras en un texto.                                        *
* Complejidad: O(len(palabaras) + len(texto) + num ocurrencias)         *
************************************************************************/

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define maxc 26     //Longitud del alfabeto
#define maxn 100    //Maximo numero de palabras
#define maxs 100000 //Maximo numero de estados

int go[maxs][maxc], nxt[maxs]; //Nodos siguientes en el Trie
bool isEnd[maxs][maxn];        //Guarda si la palabra i termina en el estado s

/*Retorna el siguiente estado*/
int nextState(int currState, int c) {
    while (go[currState][c] == -1)
        currState = nxt[currState];
    return go[currState][c];
}

/*Construye la "maquina" de patrones basada en un Trie extendido*/
void build(int n, string p[]) {
    int states = 1;
    memset(go, -1, sizeof go);
    memset(isEnd, 0, sizeof isEnd);

    /*Construye el Trie*/
    for (int i = 0; i < n; i++) {
        int currState = 0;
        for (int j = 0; j < p[i].size(); j++) {
            char c = p[i][j] - 'a';
            if (go[currState][c] == -1)
                go[currState][c] = states++;
            currState = go[currState][c];
        }
        isEnd[currState][i] = true;
    }

    for (int c = 0; c < maxc; c++)
        if (go[0][c] == -1)
            go[0][c] = 0;

    /*Calcula las aristas siguientes cuando no estan en el Trie*/
    queue<int> Q;
    memset(nxt, -1, sizeof nxt);

    for (int c = 0; c < maxc; c++)
        if (go[0][c]) {
            nxt[go[0][c]] = 0;
            Q.push(go[0][c]);
        }

    while (!Q.empty()) {
        int state = Q.front();
        Q.pop();
        for (int c = 0; c < maxc; c++)
            if (go[state][c] != -1) {
                int id = nextState(nxt[state], c);
                nxt[go[state][c]] = id;
                for (int i = 0; i < n; i++)
                    if (isEnd[id][i])
                        isEnd[go[state][c]][i] = true;
                Q.push(go[state][c]);
            }
    }
}

/*Imprime las ocurrencias de las palabras en el texto*/
void searchWords(int n, string p[], string text) {
    build(n, p);
    int currState = 0;
    for (int i = 0; i < text.size(); i++) {
        currState = nextState(currState, text[i] - 'a');
        for (int j = 0; j < n; j++)
            if (isEnd[currState][j])
                cout << p[j] << " aparece de " << i - p[j].size() + 1 << " a " << i << "\n";
    }
}

int main() {
    string s = "abcdabccabbacefdabc";
    string p[] = {"abc", "db", "ca", "bcd", "ef"};
    cout << s << "\n";
    searchWords(5, p, s);
    return 0;
}
