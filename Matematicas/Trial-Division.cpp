/*********************************************************************************
* Factorizacion en primos de un numero mediante prueba por division.             *
* Complejidad: O(pi(sqrt(n))) (peor caso)                                        *
*********************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

#define maxn 10000000     //Raiz cuadrada del mayor numero a factorizar.

long long n;               //Numero a factorizar.
vector<long long> primes;  //Lista de primos.
vector<long long> factors; //Lista de factores primos de n.

//Encuentra con la Criba de Eratostenes los primos menores que maxn.
void find_primes() {
    vector<bool> sieve(maxn);
    for (long long i = 2; i < maxn; ++i)
        if (!sieve[i]) {
            primes.push_back(i);
            for (long long j = i * i; j < maxn; j += i)
                sieve[j] = true;
        }
}

//Prueba por division.
void prime_factor() {
    factors.clear();
    for (int i = 0; primes[i] * primes[i] <= n; ++i)
        while (n % primes[i] == 0) {
            factors.push_back(primes[i]);
            n /= primes[i];
        }
    if (n != 1)
        factors.push_back(n);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    find_primes();
    while (cin >> n) {
        prime_factor();
        for (long long p : factors)
            cout << p << ' ';
        cout << '\n';
    }
    return 0;
}