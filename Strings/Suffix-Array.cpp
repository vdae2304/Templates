/*********************************************************************************
* Suffix Array + LCP Array.                                                      *
* Complejidad: O(n log n)                                                        *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;
#define maxn 100000 //Longitud maxima del string.

string word;                         //String.
int n, suffixArray[maxn], lcp[maxn]; //Arreglo de sufijos y arreglo de mayor prefijo comun.

pair<pair<int, int>, int> rnk[maxn], tmp[maxn];
int bucket[maxn];

//Ordena los rangos. Otra opcion es usar sort(), pero la complejidad sera O(n log^2 n).
void RadixSort() {
    int M = max(n, 256);
    for (int k = 0; k < 2; ++k) {
        fill(bucket, bucket + M, 0);
        for (int i = 0; i < n; ++i)
            bucket[k ? rnk[i].first.first : rnk[i].first.second]++;
        for (int i = 1; i < M; ++i)
            bucket[i] += bucket[i - 1];
        for (int i = n - 1; i >= 0; --i) 
            tmp[--bucket[k ? rnk[i].first.first : rnk[i].first.second]] = rnk[i];
        copy(tmp, tmp + n, rnk);
    }
}

//Construye el arreglo de sufijos.
void buildSA() {
    n = word.size();
    for (int i = 0; i < n; ++i)
        rnk[i] = make_pair(make_pair(word[i], word[min(i + 1, n - 1)]), i);
    RadixSort();
    for (int k = 2; k < n; k *= 2) {
        int curr = 0, prev = -1;
        for (int i = 0; i < n; ++i) {
            if (rnk[i].first != make_pair(prev, rnk[i - 1].first.second))
                curr++;
            prev = rnk[i].first.first;
            rnk[i].first.first = curr;
            suffixArray[rnk[i].second] = i;
        }
        for (int i = 0; i < n; ++i) {
            int j = min(rnk[i].second + k, n - 1);
            rnk[i].first.second = rnk[suffixArray[j]].first.first;
        }
        RadixSort();
    }
    for (int i = 0; i < n; ++i)
        suffixArray[i] = rnk[i].second;
}

//Construye el arreglo de mayor prefijo comun.
void buildLCP() {
    for (int i = 0; i < n; ++i)
        bucket[suffixArray[i]] = i;
    for (int i = 0, k = 0; i < n; ++i) {
        if (bucket[i] == n - 1) 
            k = 0;
        else {
            int j = suffixArray[bucket[i] + 1];
            while (i + k < n && j + k < n && word[i + k] == word[j + k])
                k++;
            lcp[bucket[i]] = k;
            if (k > 0)
                k--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    //Lee la palabra.
    cin >> word;
    word.push_back('$');
    //Imprime el arreglo de sufijos y lcp.
    buildSA();
    buildLCP();
    for (int i = 0; i < n; ++i)
        cout << suffixArray[i] << ' ' << lcp[i] << ": " << word.substr(suffixArray[i]) << '\n';
    return 0;
}
