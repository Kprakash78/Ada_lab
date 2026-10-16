#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

void matrixChainOrder(const vector<int>& d, vector<vector<int>>& m, vector<vector<int>>& s) {
    int n = d.size() - 1;
    m.assign(n + 1, vector<int>(n + 1, 0));
    s.assign(n + 1, vector<int>(n + 1, 0));

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + d[i - 1] * d[k] * d[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
}

string getOptimalParenthesization(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        return "M" + to_string(i);
    }
    return "(" + getOptimalParenthesization(s, i, s[i][j]) + getOptimalParenthesization(s, s[i][j] + 1, j) + ")";
}

int main() {
    vector<int> d = {30, 35, 15, 5, 10, 20, 25};

    cout << "Dimensions: ";
    for (int x : d) cout << x << " ";
    cout << "\n";

    vector<vector<int>> m, s;
    matrixChainOrder(d, m, s);

    int n = d.size() - 1;
    cout << "Minimum Multiplications : " << m[1][n] << "\n";
    cout << "Optimal Parenthesization : " << getOptimalParenthesization(s, 1, n) << "\n";

    return 0;
}
