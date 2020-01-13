/*********************************************************************************
* Test de primalidad.                                                            *
* Algoritmo de Miller Rabin para verificar si un numero es posiblemente primo    *
*********************************************************************************/

#include <iostream>
#include <random> 
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

default_random_engine gen; //Generador de numeros aleatorios.

//Regresa false si n es compuesto y true si es probablemente primo.
bool MillerTest(long long n) {
    uniform_int_distribution<long long> Rand(2, n -  2);
    long long d = (n - 1) / ((n - 1) & (1 - n));
    __int128 x = power(Rand(gen), d, n);
    if (x == 1 || x == n - 1)
        return true;
    for (; d != n - 1; d *= 2) {
        x = (x * x) % n;
        if (x == 1)
            return false;
        if (x == n - 1)
            return true;
    }
    return false;
}

//Ejecuta el Test de Miller-Rabin varias veces.
bool isProbablePrime(long long n, int attemps) {
    if (n <= 4)
        return n == 2 || n == 3;
    while (attemps--)
        if (!MillerTest(n))
            return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    long long n;
    while (cin >> n) {
        if (isProbablePrime(n, 10))
            cout << "Probablemente es primo.\n";
        else
            cout << "No es primo.\n";
    }
    return 0;
}