#include <iostream>
#include <vector>
using namespace std;

/***********************************************
* Prime factorization.                         *
* Time complexity: O(pi(sqrt(n))) (worst case) *
***********************************************/

#define maxn 10000000
vector<long long> primes;

/*Use Erathostenes sieve to find all primes smaller than 10^7*/
void find_primes() {
	vector<bool> sieve(maxn);
	for (long long i = 2; i < maxn; i++)
		if (!sieve[i]) {
			primes.push_back(i);
			for (long long j = i * i; j < maxn; j += i)
				sieve[j] = true;
		}
}

/*Use the prime list to factor n by trial division*/
void prime_factor(long long n) {
	for (int i = 0; i < primes.size() && primes[i] * primes[i] <= n; i++)
		while (n % primes[i] == 0) {
			cout << primes[i] << " ";
			n /= primes[i];
		}
	if (n != 1)    //If n doesn't have prime divisors smaller than 10^7
		cout << n; //we declare it as prime
	cout << "\n";
}

int main() {
	//Example
	long long n;
	find_primes();
	while (cin >> n) 
		prime_factor(n);
	return 0;
}