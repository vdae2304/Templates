/*********************************************************************************
* Teorema Chino del Residuo para resolver sistemas lineales de congruencias.     *
* Algoritmo Extendido de Euclides para encontrar el maximo comun divisor.        *
*********************************************************************************/

#include <iostream>
#include <utility>
using namespace std;

//Algoritmo extendido de Euclides.
long long extendedEuclid(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1; y = 0; 
        return a;
    } 
    else {
        long long gcd = extendedEuclid(b, a % b, y, x);
        y -= (a / b) * x;
        return gcd;
    }
}

//Teorema Chino del Residuo. Regresa el residuo y el modulo.
pair<long long, long long> ChineseRemainder(int n, long long coef[], long long mod[]) {
    pair<long long, long long> ans(0, 1);
    for (int i = 0; i < n; ++i)
        ans.second *= mod[i];
    for (int i = 0; i < n; ++i) {
        long long a = ans.second / mod[i], x, y;
        extendedEuclid(a, mod[i], x, y);
        long long tmp = (a * (x + ans.second)) % ans.second;
        ans.first = (ans.first + coef[i] * tmp) % ans.second;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    int n;
    cin >> n;
    //Lee los datos de las ecuaciones.
    long long coef[n], mod[n];
    for (int i = 0; i < n; ++i)
        cin >> coef[i] >> mod[i];
    //Imprime la solucion.
    pair<long long, long long> ans = ChineseRemainder(n, coef, mod);
    cout << "x = " << ans.second << "k + " << ans.first << '\n';
    return 0;
}