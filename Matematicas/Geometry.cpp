/************************************************************
* Implementacion de funciones geometricas elementales       *
************************************************************/
#include <iostream>
#include <cmath>
using namespace std;

typedef int T; //int o double

struct point {
	T x, y, z;

	point(T _x, T _y, T _z = 0) {
		x = _x;
		y = _y;
		z = _z;
	}
};

point operator + (point P, point Q) {
	return point(P.x + Q.x, P.y + Q.y, P.z + Q.z);
}

point operator * (T lambda, point P) {
	return point(lambda * P.x, lambda * P.y, lambda * P.z);
}

T DotProduct(point P, point Q) {
	return P.x*Q.x + P.y*Q.y + P.z*Q.z;
}

double norm(point P) {
	return sqrt(DotProduct(P, P));
}

double angle(point P, point Q) {
	return acos(DotProduct(P, Q) / (norm(P) * norm(Q)));
}

point CrossProduct(point P, point Q) {
	return point(P.y*Q.z - P.z*Q.y, P.z*Q.x - P.x*Q.z, P.x*Q.y - P.y*Q.x);
}

point projection(point P, point Q) {
	return (DotProduct(P, Q)/DotProduct(Q, Q)) * Q;
}

int main() {
	return 0;
}