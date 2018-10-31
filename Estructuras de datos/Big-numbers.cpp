#include <iostream>
#include <algorithm>
using namespace std;

/*Retorna el i-esimo digito de derecha a izquierda de un numero dado*/
int digit(const string &num, int i) {
    if (0 <= i && i < num.size())
        return num[num.size() - 1 - i] - '0';
    return 0;
}

/*Retorna la suma de dos numeros*/
string sum(const string &a, const string &b) {
    string res;
    int d = 0;
    for (int i = 0; i < max(a.size(), b.size()); i++, d /= 10) {
        d += digit(a, i) + digit(b, i);
        res.push_back((d % 10) + '0');
    }
    if (d > 0)
        res.push_back(d + '0');
    reverse(res.begin(), res.end());
    return res;
}

/*Retorna la diferencia (en valor absoluto) de dos numeros*/
string substract(const string &a, const string &b) {
    ;
}

/*Retorna el producto de dos numeros (string x int)*/
string multiply(const string &a, int b) {
    string res;
    int d = 0;
    for (int i = 0; i < a.size(); i++, d /= 10) {
        d += digit(a, i) * b;
        res.push_back((d % 10) + '0');
    }
    for (; d > 0; d /= 10)
        res.push_back((d % 10) + '0');
    reverse(res.begin(), res.end());
    return res;
}

/*Retorna el producto de dos numeros (string x string)*/
string multiply(const string &a, const string &b) {
    string res;
    for (int i = 0; i < b.size(); i++)
        res = sum(res, multiply(a, digit(b, i)).append(i, '0'));
    return res;
}

/*Retorna el cociente y residuo de la division (string / int)*/
pair<string, int> divide(const string &a, int b) {
    pair<string, int> res;
    for (int i = a.size() - 1; i >= 0; i--) {
        res.second = 10 * res.second + digit(a, i);
        if (!res.first.empty() || res.second >= b || i == 0)
            res.first.push_back((res.second / b) + '0');
        res.second %= b;
    }
    return res;
}

int main() {
    cout << sum("123", "5412") << endl; //5535
    cout << multiply("12425", 124) << endl; //1540700
    cout << multiply("57151290", "56186") << endl; //3211102379940
    cout << divide("158241", 821).first << " " << divide("158241", 821).second << endl; //192, 609
}
