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

void kmp_search() {
    for (int i = 0, j = 0; i < text.size(); ++i) {
        while (j > 0 && text[i] != pattern[j])
            j = lps[j - 1];
        if (text[i] == pattern[j])
            j++;
        if (j == pattern.size()) {
            cout << "Match found at " << i - j + 1 << '\n';
            j = lps[j - 1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie();
    cin >> txt >> pattern;
    kmp_preprocess();
    kmp_search();
    return 0;
}