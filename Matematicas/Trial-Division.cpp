/*********************************************************************************
* Factorizacion en primos de un numero mediante prueba por division.             *
* Complejidad: O(pi(sqrt(n))) (peor caso)                                        *
*********************************************************************************/

#include <iostream>
#include <vector>
using namespace std;
#define maxn 10000000 //Raiz cuadrada del mayor numero a factorizar.

vector<long long> primes;  //Lista de primos.

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
vector<long long> prime_factor(long long n) {
    vector<long long> factors;
    for (int i = 0; primes[i] * primes[i] <= n; ++i)
        while (n % primes[i] == 0) {
            factors.push_back(primes[i]);
            n /= primes[i];
        }
    if (n != 1)
        factors.push_back(n);
    return factors;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    long long n;
    find_primes();
    while (cin >> n) {
        for (long long p : prime_factor(n))
            cout << p << ' ';
        cout << '\n';
    }
    return 0;
}