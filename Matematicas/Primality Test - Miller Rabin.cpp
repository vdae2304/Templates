/************************************************************************
* Test de primalidad.                                                   *
* Algoritmo de Miller Rabin para verificar si un numero es posiblemente * 
* primo                                                                 *
************************************************************************/

#include <iostream>
#include <random> //C++11
using namespace std;
typedef long long lld;

/*Retorna (a * b) % m. Optimizado por si a y b son muy grandes*/
lld multmod(lld a, lld b, lld m) {
	lld ans = 0;
	for (; b > 0; a = (2 * a) % m, b /= 2) 
		ans = (ans + a * (b % 2)) % m;
	return ans;
}

/*Exponenciacion modular*/
lld power(lld b, lld e, lld m) {
	if (e == 0)
		return 1;
	else if (e % 2)
		return multmod(b, power(b, e - 1, m), m);
	else {
		lld p = power(b, e / 2, m);
		return multmod(p, p, m);	
	}
}

default_random_engine gen;

/*Retorna false si n es compuesto y true si es probablemente primo*/
bool MillerTest(lld n, lld d) {
	uniform_int_distribution<lld> Rand(2, n -  2);
	lld x = power(Rand(gen), d, n);
	if (x == 1 || x == n - 1)
		return true;
	for (; d != n - 1; d *= 2) {
		x = multmod(x, x, n);
		if (x == 1)
			return false;
		if (x == n - 1)
			return true;
	}
	return false;
}

/*Ejecuta el Test de Miller-Rabin varias veces.*/
bool isProbablePrime(lld n, int attemps) {
	if (n == 2 || n == 3)
		return true;
	if (n <= 4)
		return false;
	lld d = n - 1;
	for (; d % 2 == 0; d /= 2);
	while (attemps--)
		if (!MillerTest(n, d))
			return false;
	return true;
}

int main() {
	lld n;
	while (cin >> n) 
		cout << (isProbablePrime(n, 10) ? "Primo\n" : "No primo\n");
	return 0;
}