/*********************************************************************************
* Big Numbers                                                                    *
* Operaciones aritmeticas para numeros no negativos arbitrariamente grandes      *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

typedef string BigInteger;

//Regresa el i-esimo digito de derecha a izquierda de un numero.
int digit(const BigInteger &num, int i) {
    if (i < num.size())
        return num[num.size() - 1 - i] - '0';
    return 0;
}

//Compara dos numeros y regresa: 1 si el primero es mayor; 0 si son iguales; -1 si el segundo es mayor.
int compareTo(const BigInteger &a, const BigInteger &b) {
    for (int i = max(a.size(), b.size()) - 1; i >= 0; --i) {
        if (digit(a, i) > digit(b, i))
            return 1;
        if (digit(b, i) > digit(a, i))
            return -1;
    }
    return 0;
}

//Regresa la suma de dos numeros.
BigInteger sum(const BigInteger &a, const BigInteger &b) {
    BigInteger ans;
    int carry = 0;
    for (int i = 0; i < max(a.size(), b.size()); ++i) {
        carry += digit(a, i) + digit(b, i);
        ans.push_back((carry % 10) + '0');
        carry /= 10;
    }
    if (carry)
        ans.push_back(carry + '0');
    reverse(ans.begin(), ans.end());
    return ans;
}

//Regresa la diferencia de dos numeros. El primer numero debe ser mayor o igual que el segundo.
BigInteger substract(const BigInteger &a, const BigInteger &b) {
    BigInteger ans;
    int carry = 0;
    for (int i = 0; i < a.size(); ++i) {
        carry += digit(a, i) - digit(b, i);
        if (carry >= 0) {
            ans.push_back(carry + '0');
            carry = 0;
        }
        else {
            ans.push_back(carry + 10 + '0');
            carry = -1;
        }
    }
    while (ans.size() > 1 && ans.back() == '0')
        ans.pop_back();
    reverse(ans.begin(), ans.end());
    return ans;
}

//Regresa el producto de dos numeros (BigInteger x int).
BigInteger multiply(const BigInteger &a, int b) {
    if (b == 0)
        return "0";
    BigInteger ans;
    int carry = 0;
    for (int i = 0; i < a.size(); ++i) {
        carry += digit(a, i) * b;
        ans.push_back((carry % 10) + '0');
        carry /= 10;
    }
    while (carry) {
        ans.push_back((carry % 10) + '0');
        carry /= 10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

//Regresa el producto de dos numeros (BigInteger x BigInteger).
BigInteger multiply(const BigInteger &a, const BigInteger &b) {
    BigInteger ans;
    for (int i = 0; i < b.size(); ++i)
        ans = sum(ans, multiply(a, digit(b, i)).append(i, '0'));
    return ans;
}

//Regresa el cociente y el residuo de la division (BigInteger / int).
pair<BigInteger, int> divide(const BigInteger &a, int b) {
    pair<BigInteger, int> ans;
    for (int i = a.size() - 1; i >= 0; --i) {
        ans.second = 10*ans.second + digit(a, i);
        if (!ans.first.empty() || ans.second >= b || i == 0)
            ans.first.push_back((ans.second / b) + '0');
        ans.second %= b;
    }
    return ans;
}

//Regresa el cociente y el residuo de la division (BigInteger / BigInteger).
pair<BigInteger, BigInteger> divide(const BigInteger &a, const BigInteger &b) {
    pair<BigInteger, BigInteger> ans;
    BigInteger table[10];
    for (int i = 0; i < 10; ++i)
        table[i] = multiply(b, i);
    for (int i = a.size() - 1; i >= 0; --i) {
        int q = 0;
        ans.second.push_back(digit(a, i) + '0');
        while (q < 9 && compareTo(ans.second, table[q + 1]) >= 0)
            ++q;
        if (!ans.first.empty() || q > 0 || i == 0)
            ans.first.push_back(q + '0');
        ans.second = substract(ans.second, table[q]);
    }
    return ans;
}

int main() {
    BigInteger a, b;
    cin >> a >> b;

    cout << a << " + " << b << " = " << sum(a, b) << '\n';
    if (compareTo(a, b) >= 0)
        cout << a << " - " << b << " = " << substract(a, b) << '\n';
    else
        cout << b << " - " << a << " = " << substract(b, a) << '\n';    
    cout << a << " * " << b << " = " << multiply(a, b) << '\n';
    cout << a << " = " << b << " * " << divide(a, b).first << " + " << divide(a, b).second << '\n';

    return 0;
}
