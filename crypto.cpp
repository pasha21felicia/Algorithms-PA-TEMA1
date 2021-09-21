#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
using namespace std;


int main(int argc, char const *argv[]) {
	ifstream fin("crypto.in");
	ofstream fout("crypto.out");

	vector < pair <int, int> > vect;
	int N, B;
	int p, u;

	fin >> N >> B;

	for (int i = 0; i < N; i++) {
		fin >> p >> u;
		vect.push_back(make_pair(p, u));
	}
	sort(vect.begin(), vect.end());  // sortez dupa primul element

	int result = vect[0].first;
	int i = 0;
	int sum = 0;
	while (i <= N && sum <= B) {
		// daca elementele consecutive sunt egale, adun suma
		if (vect[i].first == result && vect[i].first == vect[i+1].first) {
			sum += vect[i].second;
			// conditie de terminare cazul ca suma viitoare > B
			if (vect[i].second + vect[i+1].second > B) {
				break;
			}
			i++;
		// elementele consecutive nu sunt egale iar result == curent
		} else if (vect[i].first == result
					&& (i == N-1 || vect[i].first != vect[i+1].first)) {
			sum += vect[i].second;
			B -= sum;
			result++;
			i++;
		// elementele consecutive nu sunt egale iar result > curent
		} else if (vect[i].first > result) {
			if (vect[i].first >= 2 * result && sum*result <= B) {
				B -= sum * result;
				result = result * 2;  // mica imbunatatire de performanta
			} else {
				B -= sum;
				result++;
			}
		}
	}
	fout << result;
	return 0;
}

