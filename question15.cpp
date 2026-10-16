#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int longestConvexSubsequence(const vector<int>& A, vector<int>& sequence) {
    int n = A.size();
    if (n == 0) return 0;
    if (n == 1) {
        sequence = {A[0]};
        return 1;
    }

    vector<vector<int>> dp(n, vector<int>(n, 2));
    vector<vector<int>> parent(n, vector<int>(n, -1));

    int maxLen = 2;
    int best_j = 0, best_i = 1;

    for (int j = 0; j < n; j++) {
        for (int i = j + 1; i < n; i++) {
            for (int k = 0; k < j; k++) {
                if (1LL * A[i] - A[j] > 1LL * A[j] - A[k]) {
                    if (dp[k][j] + 1 > dp[j][i]) {
                        dp[j][i] = dp[k][j] + 1;
                        parent[j][i] = k;
                    }
                }
            }
            if (dp[j][i] > maxLen) {
                maxLen = dp[j][i];
                best_j = j;
                best_i = i;
            }
        }
    }

    int curr_i = best_i;
    int curr_j = best_j;
    sequence.push_back(A[curr_i]);
    sequence.push_back(A[curr_j]);

    while (parent[curr_j][curr_i] != -1) {
        int k = parent[curr_j][curr_i];
        sequence.push_back(A[k]);
        curr_i = curr_j;
        curr_j = k;
    }
    reverse(sequence.begin(), sequence.end());

    return maxLen;
}

int main() {
    vector<int> A = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 7};

    cout << "Array: ";
    for (int x : A) cout << x << " ";
    cout << "\n";

    vector<int> sequence;
    int len = longestConvexSubsequence(A, sequence);

    cout << "Longest Convex Subsequence Length : " << len << "\n";
    cout << "Longest Convex Subsequence        : ";
    for (int x : sequence) cout << x << " ";
    cout << "\n";

    return 0;
}
