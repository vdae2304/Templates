/*********************************************************************************
* Teorema Chino del Residuo para resolver sistemas lineales de congruencias.     *
* Complejidad: O(n)                                                              *
*********************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

#define maxn 100000    //Maximo numero de ecuaciones.
typedef long long lld;

int n;                          //Numero de ecuaciones.
lld MOD, coef[maxn], mod[maxn]; //Ecuaciones.

//Algoritmo extendido de Euclides.
lld extendedEuclid(lld a, lld b, lld &x, lld &y) {
    if (b == 0) {
        x = 1; y = 0; 
        return a;
    }
    else {
        lld gcd = extendedEuclid(b, a % b, y, x, gcd);
        y -= (a / b) * x;
        return gcd;
    }
}

//Teorema Chino del Residuo.
lld ChineseRemainder() {
    MOD = 1;
    for (int i = 0; i < n; ++i)
        MOD *= mod[i];

    lld x = 0;
    for (int i = 0; i < n; ++i) {
        lld N = MOD / mod[i], invN, invmod;
        extendedEuclid(N, mod[i], invN, invmod);
        x += coef[i] * invN * N;
    }

    return x;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> coef[i] >> mod[i];

    cout << "x = " << ChineseRemainder() << " mod " << MOD << '\n';
    return 0;
}