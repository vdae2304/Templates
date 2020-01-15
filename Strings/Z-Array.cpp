/*********************************************************************************
* Arreglo Z para busqueda de patrones.                                           *
* Complejidad: O(n)                                                              *
*********************************************************************************/

#include <iostream>
using namespace std;
#define maxn 100000 //Longitud maxima de los strings.

string text, pattern, str; //Texto, patron a buscar y string auxiliar.
int Z[maxn];               //Arreglo Z.

//Construye el arreglo Z de str.
void buildZ() {
    int l = 0, r = 0;
    for (int i = 1; i < str.size(); ++i) {
        Z[i] = 0;
        if (i <= r)
            Z[i] = min(r - i + 1, Z[i - l]);
        while (i + Z[i] < str.size() && str[Z[i]] == str[i + Z[i]])
            Z[i]++;
        if (i + Z[i] - 1 > r) {
            l = i;
            r = i + Z[i] - 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    //Lee el texto y los patrones.
    cin >> text >> pattern;
    str = pattern + '$' + text;    
    //Imprime todas las ocurrencias.
    buildZ();
    for (int i = 0; i < text.size(); ++i)
        if (Z[i + pattern.size() + 1] == pattern.size())
            cout << "Ocurrencia en la posicion " << i << '\n';
    return 0;
}