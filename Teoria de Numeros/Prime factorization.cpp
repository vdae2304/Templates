#include <iostream>
using namespace std;

/*******************************************
* Prime factorization.                     *
* Time complexity: O(sqrt(n)) (worst case) *
*******************************************/

void prime_factor(long long n) {
	for (long long i = 2; i * i <= n; i++)
		while (n % i == 0) {
			cout << i << " ";
			n /= i;
		}
	if (n != 1)
		cout << n;
	cout << "\n";
}

int main() {
	//Example
	long long n;
	while (cin >> n) 
		prime_factor(n);
	return 0;
}