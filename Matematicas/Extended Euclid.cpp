/*************************************************************
* Algoritmo extendido de Euclides para resolver la ecuacion  *
* diofantica ax + by = gcd(x, y)                             *
*************************************************************/

#include <iostream>
using namespace std;
typedef long long lld;

lld extendedEuclid(lld a, lld b, lld &x, lld &y, lld &d) {
	if (b == 0) {
		x = 1; y = 0; d = a;
	}
	else {
		extendedEuclid(b, a % b, y, x, d);
		y -= (a / b) * x;
	}
}

int main() {
	lld a, b, x, y, d;
	while (cin >> a >> b) {
		extendedEuclid(a, b, x, y, d);
		cout << a << " * " << x << " + " << b << " * " << y << " = " << d << "\n";
	}
	return 0;
}