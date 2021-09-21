#include <bits/stdc++.h>
#include <algorithm>
#include <fstream>

using namespace std;


int main(int argc, char const *argv[]) {
	ifstream fin("valley.in");
	ofstream fout("valley.out");

	int N;
	fin >> N;
	// vectorul citit din input
	vector <long long > heights;
	// mentine elementul cel mai mic din stanga lui height(i)
	vector <long long > leftMin;
	// mentine elementul cel mai mic din dreapta lui height(i)
	vector <long long > rightMin;
	// mentine neajunsuri din stanga pentru a crea o vale
	vector <long long > makeLeft;
	// mentine neajunsuri din dreapta pentru a crea o vale
	vector <long long > makeRight;
	heights.reserve(N);
	leftMin.reserve(N);
	rightMin.reserve(N);
	makeLeft.reserve(N);
	makeRight.reserve(N);

	for (int i = 0; i < N; i++) {
		fin >> heights[i];
	}

	// creez vectorul leftMin
	leftMin[0] = 0;
	leftMin[1] = min(heights[0], heights[1]);
	for (int i = 2; i < N; i++) {
		if (heights[i] <= leftMin[i-1])
			leftMin[i] = heights[i];
		else
			leftMin[i] = leftMin[i-1];
	}

	// creez vectorul rightMin
	rightMin[N-1] = 0;
	rightMin[N-2] = min(heights[N-1], heights[N-2]);
	for (int i = N-3; i >= 0; i--) {
		if (heights[i] <= rightMin[i+1])
			rightMin[i] = heights[i];
		else
			rightMin[i] = rightMin[i+1];
	}

	// creez vectorul de neajunsuri din stanga
	makeLeft[0] = 0;
	for (int i = 1; i < N; i++) {
		makeLeft[i] = heights[i]-leftMin[i];
	}

	// creez vectorul de neajunsuri din dreapta
	makeRight[N-1] = 0;
	for (int i = N-2; i >= 0; i--) {
		makeRight[i] = heights[i] - rightMin[i];
	}

	// gasesc cel mai jos punct din vale (hole)
	long long hole = 0;
	for (int i = 1; i < N-1; i++)
		// conditia de a gasi hole este ca vectorii astea == 0 undeva
		if (makeRight[i] == 0 && makeLeft[i] == 0) {
			hole = i;
			break;
		}

	long long result = 0;
	if (hole != 0) {  // daca s-a gasit vale
		for (int i = 1; i < N-1; i++) {
			// fac suma minimurilor din cei doi vectori de neajunsuri
			result += min(makeLeft[i], makeRight[i]);
		}
	} else {  // daca nu s-a gasit hole (nu avea forma de vale initial)
		vector< pair <long long, long long> > vect;
		for (int i = 0; i < N; i++) {  // creez un vector de perechi
			vect.push_back(make_pair(makeLeft[i], makeRight[i]));
		}
		pair <long long, long long> maxPair = vect[1];
		for (int i = 1; i < N-1; i++) {
			if (vect[i].first <= maxPair.first && vect[i].second <= maxPair.second)
				maxPair = vect[i];
		}
		// rezultatul va fi maximul din cadrul perechii minime
		result += max(maxPair.first, maxPair.second);
	}

	fout << result;
	return 0;
}
