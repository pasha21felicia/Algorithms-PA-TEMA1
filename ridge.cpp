#include <bits/stdc++.h>
#include <fstream>
#define MIN 1000000000000000000;
using namespace std;


vector<vector<long long> > minimize(int N, vector <long long> heights,
											vector <long long> cost) {
	vector<vector<long long> > v(N, vector<long long>(4));
	// cazurile de baza
	int costisor = 0;
	for (int i = 0; i < 3; i++) {
		v[0][i] = costisor;
		costisor += cost[0];
	}
	v[0][3] = 4*cost[0];
	long long mini;

	for (int i = 1; i < N; i++) {
		for (int j = 0; j < 4; j++) {
			mini = MIN;
			if (heights[i]-j >= 0) {
				if (heights[i]-j != heights[i-1])
					if (v[i-1][0] <= mini)
						mini = v[i-1][0];
				if (heights[i]-j != heights[i-1]-1)
					if (v[i-1][1] <= mini)
						mini = v[i-1][1];
				if (heights[i]-j != heights[i-1]-2)
					if (v[i-1][2] <= mini)
						mini = v[i-1][2];
				if (heights[i]-j != heights[i-1]-3)
					if (v[i-1][3] <= mini)
						mini = v[i-1][3];
				v[i][j] = j*cost[i] + mini;
			} else {
				v[i][j] = mini;  // i-a minimul din toate cazurile
			}
		}
	}
	return v;
}
long long getMinimum(vector<vector<long long> > v, int N) {
	long long mini = MIN;
	for (int i = 0; i < 4; i++) {
		if (mini >= v[N-1][i])
			mini = v[N - 1][i];
	}
	return mini;
}
int main() {
	ifstream fin("ridge.in");
	ofstream fout("ridge.out");

	int N, h_i, cost_i;
	vector <long long> heights;
	vector <long long> cost;
	fin >> N;
	heights.reserve(N);
	cost.reserve(N);

	for (int i = 0; i < N; i++) {
		fin >> h_i >> cost_i;
		heights.push_back(h_i);
		cost.push_back(cost_i);
	}

	vector<vector<long long> > vectResult = minimize(N, heights, cost);
	long long result = getMinimum(vectResult, N);
	fout << result;

	return 0;
}
