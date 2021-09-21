#include <bits/stdc++.h>
#include <fstream>
using namespace std;

ifstream fin("stocks.in");
ofstream fout("stocks.out");

int rucsac(int N, int B, int L, vector<int> &curr,
                                vector<int> &mini,
                                vector<int> &maxi) {
    vector< vector <vector<int> > >
        dp(N + 1, vector<vector<int>>(B + 1, vector<int>(L+1)));
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= B; j++) {
            for (int l = 0; l <= L; l++) {
                if (i == 0 || j == 0 || l == 0)
                    dp[i][j][l] = 0;
                else if (j - curr[i-1] >= 0 && l - (curr[i-1] - mini[i-1]) >= 0)
                    dp[i][j][l] = max((maxi[i-1]-curr[i-1]) +
                                dp[i-1][j - curr[i-1]][l-(curr[i-1]-mini[i-1])],
                                dp[i-1][j][l]);  // folosesc obiectul i
                else
                    dp[i][j][l] = dp[i-1][j][l];  // nu folosesc obiectul i
            }
        }
    }
    return dp[N][B][L];
}
int main(int argc, char const *argv[]) {
    int N, B, L;
    int curr, mini, maxi;
    fin >> N >> B >> L;

    vector <int> currentValue;
    vector <int> minValue;
    vector <int> maxValue;

    currentValue.reserve(N+1);
    minValue.reserve(N+1);
    maxValue.reserve(N+1);

    for (int i = 0; i < N; i++) {
        fin >> curr >> mini >> maxi;
        currentValue.push_back(curr);
        minValue.push_back(mini);
        maxValue.push_back(maxi);
    }
    int result = rucsac(N, B, L, currentValue, minValue, maxValue);
    fout << result;
    return 0;
}
