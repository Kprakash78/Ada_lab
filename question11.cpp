#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string lcs(const string &A, const string &B) {
    int n = A.size();
    int m = B.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }


    string result = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1]) {
            result += A[i - 1];
            --i; --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    reverse(result.begin(), result.end());
    return result;
}

int main() {
    string A, B;

    cout << "Enter sequence A: ";
    cin >> A;

    cout << "Enter sequence B: ";
    cin >> B;

    string result = lcs(A, B);

    cout << "\nSequence A         : " << A << "  (n = " << A.size() << ")\n";
    cout << "Sequence B         : " << B << "  (m = " << B.size() << ")\n";
    cout << "LCS Length         : " << result.size() << "\n";
    cout << "LCS                : " << result << "\n";

    return 0;
}

