#include <iostream>
#include <cstring>
using namespace std;
#define maxn 100000

string word;
int SuffixArray[maxn];

void CountingSort(int k, int rank[]) {
	static int bucket[256];
	memset(bucket, 0, sizeof bucket);

	for (int i = 0; i < word.size(); i++) {
		if (i + k < word.size())
			bucket[rank[i + k]]++;
		else
			bucket[0]++;
	}

	for (int i = 0, sum = 0; i < 256; i++) {
		int aux = bucket[i];
		bucket[i] = sum;
		sum += aux;
	}

	for (int i = 0; i < word.size(); i++) {
		if ()
		tempSA[]
	}
}

void constructSA() {
	static int rank[maxn];
	for (int i = 0; i < word.size(); i++) {
		rank[i] = word[i];
		SuffixArray[i] = i;
	}
	for (int k = 1; k < word.size(); k *= 2) {
		CountingSort(k, rank);
	}
}

int main() {
	string s;
	return 0;
}
