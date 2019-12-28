/*********************************************************************************
* Teorema Chino del Residuo para resolver sistemas lineales de congruencias.     *
* Algoritmo Extendido de Euclides para encontrar el maximo comun divisor.        *
*********************************************************************************/

#include <iostream>
using namespace std;

#define maxn 100000    //Maximo numero de ecuaciones.

int n;                                //Numero de ecuaciones.
long long MOD, coef[maxn], mod[maxn]; //Datos de las ecuaciones.

//Algoritmo extendido de Euclides.
long long extendedEuclid(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1; 
        y = 0; 
        return a;
    }
    else {
        long long gcd = extendedEuclid(b, a % b, y, x);
        y -= (a / b) * x;
        return gcd;
    }
}

//Teorema Chino del Residuo.
long long ChineseRemainder() {
    MOD = 1;
    for (int i = 0; i < n; ++i)
        MOD *= mod[i];

    long long x = 0;
    for (int i = 0; i < n; ++i) {
        long long N = MOD / mod[i], invN, invM;
        extendedEuclid(N, mod[i], invN, invM);
        x = (x + coef[i] * N * invN) % MOD;
        x = (x + MOD) % MOD;
    }

    return x;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> coef[i] >> mod[i];

    cout << "x = " << ChineseRemainder() << " (mod " << MOD << ")\n";
    return 0;
}