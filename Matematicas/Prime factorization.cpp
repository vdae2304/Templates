/************************************************************
* Factorizacion en primos de un numero                      *
* Complejidad: O(pi(sqrt(n))) (peor caso)                   *
************************************************************/

#include <iostream>
#include <vector>
using namespace std;

#define maxn 10000000
vector<long long> primes;

/*Encuentra con la Criba de Eratostenes los primos menores o iguales que 10^7*/
void find_primes() {
	vector<bool> sieve(maxn);
	for (long long i = 2; i < maxn; i++)
		if (!sieve[i]) {
			primes.push_back(i);
			for (long long j = i * i; j < maxn; j += i)
				sieve[j] = true;
		}
}

/*Con ayuda de la lista de primos, encuentra los factores primos de n*/
void prime_factor(long long n) {
	for (int i = 0; i < primes.size() && primes[i] * primes[i] <= n; i++)
		while (n % primes[i] == 0) {
			cout << primes[i] << " ";
			n /= primes[i];
		}
	if (n != 1)    
		cout << n; 
	cout << "\n";
}

int main() {	
	long long n;
	find_primes();
	while (cin >> n) 
		prime_factor(n);
	return 0;
}