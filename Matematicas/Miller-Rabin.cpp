/*********************************************************************************
* Test de primalidad.                                                            *
* Algoritmo de Miller Rabin para verificar si un numero es primo                 *
*********************************************************************************/

#include <iostream>
using namespace std;

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

//Regresa true n es primo.
bool isPrime(long long n) {
    if (n <= 4)
        return n == 2 || n == 3;
    long long s, d = n - 1;
    for (s = 0; d % 2 == 0; ++s) 
        d /= 2;
    for (long long a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
    	    return true;
        if (!MillerTest(n, a, s, d))
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    long long n;
    while (cin >> n) {
        if (isPrime(n))
            cout << "Es primo.\n";
        else
            cout << "No es primo.\n";
    }
    return 0;
}