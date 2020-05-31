/*********************************************************************************
* Arreglo de KMP (Knuth-Morris-Pratt) para busqueda de patrones.                 *
* Complejidad: O(len(text) + len(pattern))                                       *
*********************************************************************************/

#include <iostream>
using namespace std;
#define maxn 100000

string text, pattern; //Texto y patron.
int lps[maxn];        //Mayor prefijo que es sufijo propio.

void kmp_preprocess() {
    lps[0] = 0;
    for (int i = 1; i < pattern.size(); ++i) {
        int j = lps[i - 1];
        while (j > 0 && pattern[i] != pattern[j])
            j = lps[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        lps[i] = j;
    }
}

//Imprime todas las ocurrencias de pattern en text.
void kmp_search() {
	kmp_preprocess();
    for (int i = 0, j = 0; i < text.size(); ++i) {
        while (j > 0 && text[i] != pattern[j])
            j = lps[j - 1];
        if (text[i] == pattern[j])
            j++;
        if (j == pattern.size()) {
            cout << "Ocurrencia en la posicion " << i - j + 1 << '\n';
            j = lps[j - 1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie();
    cin >> text >> pattern;
    kmp_search();
    return 0;
}