/*********************************************************************************
* Big Numbers                                                                    *
* Operaciones aritmeticas para numeros no negativos arbitrariamente grandes      *
*********************************************************************************/

#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

typedef string BigInt;

//Regresa el i-esimo digito de derecha a izquierda de un numero.
unsigned int digit(const BigInt &num, unsigned int i) {
    if (i < num.size())
        return num[num.size() - 1 - i] - '0';
    return 0;
}

//Compara dos numeros y regresa: 1 si el primero es mayor; 0 si son iguales; -1 si el segundo es mayor.
int compareTo(const BigInt &a, const BigInt &b) {
    for (int i = max(a.size(), b.size()) - 1; i >= 0; --i) {
        if (digit(a, i) > digit(b, i))
            return 1;
        if (digit(b, i) > digit(a, i))
            return -1;
    }
    return 0;
}

//Regresa la suma de dos numeros.
BigInt sum(const BigInt &a, const BigInt &b) {
    BigInt ans;
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
BigInt substract(const BigInt &a, const BigInt &b) {
    BigInt ans;
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

//Regresa el producto de dos numeros (BigInt x int).
BigInt multiply(const BigInt &a, unsigned int b) {
    if (b == 0)
        return "0";
    BigInt ans;
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

//Regresa el producto de dos numeros (BigInt x BigInt).
BigInt multiply(const BigInt &a, const BigInt &b) {
    BigInt ans;
    for (int i = 0; i < b.size(); ++i)
        ans = sum(ans, multiply(a, digit(b, i)).append(i, '0'));
    return ans;
}

//Regresa el cociente y el residuo de la division (BigInt / int).
pair<BigInt, unsigned int> divide(const BigInt &a, unsigned int b) {
    pair<BigInt, int> ans;
    for (int i = a.size() - 1; i >= 0; --i) {
        ans.second = 10*ans.second + digit(a, i);
        if (!ans.first.empty() || ans.second >= b || i == 0)
            ans.first.push_back((ans.second / b) + '0');
        ans.second %= b;
    }
    return ans;
}

//Regresa el cociente y el residuo de la division (BigInt / BigInt).
pair<BigInt, BigInt> divide(const BigInt &a, const BigInt &b) {
    pair<BigInt, BigInt> ans;
    BigInt table[10];
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
    BigInt a, b;
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
