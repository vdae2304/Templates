/*********************************************************************************
* Big Numbers                                                                    *
* Implementacion de operaciones aritmeticas para numeros arbitrariamente grandes *
*********************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

/*Retorna el i-esimo digito de derecha a izquierda de un numero dado*/
int digit(const string &num, int i) {
    if (0 <= i && i < num.size())
        return num[num.size() - 1 - i] - '0';
    return 0;
}

/*Compara dos numeros y retorna 1 si el primero es mayor, 0 si son iguales y -1 si el segundo es mayor*/
int compare_num(const string &a, const string &b) {
    for (int i = max(a.size(), b.size()) - 1; i >= 0; i--) {
        if (digit(a, i) > digit(b, i))
            return 1;
        if (digit(b, i) > digit(a, i))
            return -1;
    }
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
    if (compare_num(a, b) == -1)
        return substract(b, a);
    string res;
    for (int i = 0, d = 0; i < a.size(); i++) {
        d += digit(a, i) - digit(b, i);
        if (d >= 0) {
            res.push_back(d + '0');
            d = 0;
        }
        else {
            res.push_back(d + 10 + '0');
            d = -1;
        }
    }
    while (res.size() > 1 && res.back() == '0')
        res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

/*Retorna el producto de dos numeros (string x int)*/
string multiply(const string &a, int b) {
    if (b == 0)
        return "0";
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

/*Retorna el cociente y residuo de la division (string / string)*/
pair<string, string> divide(const string &a, const string &b) {
    pair<string, string> res;
    for (int i = a.size() - 1; i >= 0; i--) {
        res.second.push_back(digit(a, i) + '0');
        int d;
        for (d = 0; d < 10; d++)
            if (compare_num(res.second, multiply(b, d + 1)) == -1)
                break;
        if (!res.first.empty() || d > 0 || i == 0)
            res.first.push_back(d + '0');
        res.second = substract(res.second, multiply(b, d));
    }
    return res;
}

/*Retorna la potencia entre dos numeros (string ^ int)*/
string power(const string &a, int b) {
    if (b == 0)
        return "1";
    string p = power(a, b / 2);
    p = multiply(p, p);
    if (b % 2 == 1)
        return multiply(a, p);
    return p;
}

int main() {
    cout << sum("123", "5412") << endl; //5535
    cout << substract("155612", "2198") << endl; //153414
    cout << multiply("12425", 124) << endl; //1540700
    cout << multiply("57151290", "56186") << endl; //3211102379940
    cout << divide("158241", 821).first << " " << divide("158241", 821).second << endl; //192, 609
    cout << divide("591625125", "5125").first << " " << divide("591625125", "5125").second << endl; //115439, 250
    cout << power("1252", 10) << endl; //9463314832177962530018006401024
    return 0;
}
