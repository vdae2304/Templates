/*********************************************************************************
* Suffix Array.                                                                  *
* Complejidad: O(n log n)                                                        *
*********************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

#define maxn 100000 //Longitud maxima del string.

string word;              //String.
int n, SuffixArray[maxn]; //Arreglo de sufijos.

int rnk[maxn][2], bucket[maxn];    //Rango (SuffixArray) y Cubeta (RaxixSort).
int tempSA[maxn], tempRA[maxn][2]; //Arreglos temporales.

//Ordena de acuerdo a los rangos.
void RadixSort() {
    int M = max(n, 256);
    for (int k = 1; k >= 0; --k) {
        fill_n(bucket, M, 0);

        for (int i = 0; i < n; ++i)
            ++bucket[rnk[i][k]];
        for (int i = 1; i < M; ++i)
            bucket[i] += bucket[i - 1];

        for (int i = n - 1; i >= 0; --i) {
            int nxt_id = --bucket[rnk[i][k]];
            tempSA[nxt_id] = SuffixArray[i];
            tempRA[nxt_id][0] = rnk[i][0];
            tempRA[nxt_id][1] = rnk[i][1];
        }
        for (int i = 0; i < n; ++i) {
            SuffixArray[i] = tempSA[i];
            rnk[i][0] = tempRA[i][0];
            rnk[i][1] = tempRA[i][1];
        }
    }
}

//Construye el arreglo de sufijos.
void buildSA() {
    n = word.size();
    for (int i = 0; i < n; ++i) {
        SuffixArray[i] = i;
        rnk[i][0] = word[i];
    }
    RadixSort();

    for (int k = 1; k < n; k *= 2) {
        int curr = 0, prev = rnk[0][0];
        rnk[0][0] = curr;
        tempSA[SuffixArray[0]] = 0;

        for (int i = 1; i < n; ++i) {
            if (rnk[i][0] != prev || rnk[i][1] != rnk[i - 1][1])
                ++curr;
            prev = rnk[i][0];
            rnk[i][0] = curr;
            tempSA[SuffixArray[i]] = i;
        }

        for (int i = 0; i < n; ++i) {
            int nxt_id = SuffixArray[i] + k;
            rnk[i][1] = (nxt_id < n) ? rnk[tempSA[nxt_id]][0] : 0;
        }
        RadixSort();
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> word;

    buildSA();
    for (int i = 0; i < n; ++i) {
        cout << SuffixArray[i] << ' ';
        for (int j = SuffixArray[i]; j < n; ++j)
            cout << word[j];
        cout << '\n';
    }

    return 0;
}
