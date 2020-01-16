/*********************************************************************************
* Suffix Array.                                                                  *
* Complejidad: O(n log n)                                                        *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;
#define maxn 100000 //Longitud maxima del string.

string word;              //String.
int n, SuffixArray[maxn]; //Arreglo de sufijos.

int bucket[maxn], tempSA[maxn];         //Cubeta (RadixSort).
pair<int, int> rnk[maxn], tempRA[maxn]; //Rango (SuffixArray).

//Ordena de acuerdo a los rangos.
void RadixSort() {
    int M = max(n + 1, 256);
    for (int k = 0; k < 2; ++k) {
        fill_n(bucket, M, 0);
        for (int i = 0; i < n; ++i)
            bucket[k ? rnk[i].first : rnk[i].second]++;
        for (int i = 1; i < M; ++i)
            bucket[i] += bucket[i - 1];
        for (int i = n - 1; i >= 0; --i) {
            int nxt_id = --bucket[k ? rnk[i].first : rnk[i].second];
            tempSA[nxt_id] = SuffixArray[i];
            tempRA[nxt_id] = rnk[i];
        }
        copy(tempSA, tempSA + n, SuffixArray);
        copy(tempRA, tempRA + n, rnk);
    }
}

//Construye el arreglo de sufijos.
void buildSA() {
    n = word.size();
    for (int i = 0; i < n; ++i) {
        SuffixArray[i] = i;
        rnk[i] = make_pair(word[i], (i + 1 < n) ? word[i + 1] : 0);
    }
    RadixSort();
    for (int k = 2; k < n; k *= 2) {
        int curr = 0, prev = -1;
        for (int i = 0; i < n; ++i) {
            if (rnk[i].first != prev || rnk[i].second != rnk[i - 1].second)
                curr++;
            prev = rnk[i].first;
            rnk[i].first = curr;
            tempSA[SuffixArray[i]] = i;
        }
        for (int i = 0; i < n; ++i) {
            int nxt_id = SuffixArray[i] + k;
            rnk[i].second = (nxt_id < n) ? rnk[tempSA[nxt_id]].first : 0;
        }
        RadixSort();
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    //Lee la palabra.
    cin >> word;
    buildSA();
    //Imprime los sufijos en orden lexicografico.
    for (int i = 0; i < n; ++i) 
        cout << SuffixArray[i] << ' ';
    cout << '\n';
    return 0;
}
