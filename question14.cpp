#include <bits/stdc++.h>
using namespace std;

int longestPalindromeSubsequence(vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) dp[i][j] = dp[i + 1][j - 1] + 2;
            else dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    return dp[0][n - 1];
}

int main() {
    vector<int> a = {7, 2, 9, 4, 2, 7, 5, 9, 1, 4, 7, 2, 8, 9, 5, 7, 3, 2, 4, 9};
    cout << longestPalindromeSubsequence(a) << "\n";
}