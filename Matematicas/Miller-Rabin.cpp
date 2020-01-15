/*********************************************************************************
* Test de primalidad.                                                            *
* Algoritmo de Miller Rabin para verificar si un numero es posiblemente primo    *
*********************************************************************************/

#include <iostream>
#include <cstdlib> 
using namespace std;

//Regresa base^expo % mod.
long long power(__int128 base, long long expo, long long mod) {
    if (expo == 0)
        return 1;
    else if (expo % 2)
        return (base * power(base, expo - 1, mod)) % mod;
    else {
        __int128 p = power(base, expo / 2, mod);
        return (p * p) % mod;
    }
}

//Regresa false si n es compuesto y true si probablemente es primo.
bool MillerTest(long long n, long long a, int s, long long d) {
    __int128 x = power(a, d, n);
    if (x == 1 || x == n - 1)
        return true;
    for (int r = 0; r < s - 1; ++r) {
        x = (x * x) % n;
        if (x == n - 1)
            return true;
    }
    return false;
}

//Ejecuta el Test de Miller-Rabin varias veces.
bool isProbablePrime(long long n, int attemps) {
    if (n <= 4)
        return n == 2 || n == 3;
    long long s, d = n - 1;
    for (s = 0; d % 2 == 0; ++s) 
        d /= 2;
    while (attemps--)
        if (!MillerTest(n, 2 + rand() % (n - 3), s, d))
            return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    long long n;
    while (cin >> n) {
        if (isProbablePrime(n, 5))
            cout << "Probablemente es primo.\n";
        else
            cout << "No es primo.\n";
    }
    return 0;
}