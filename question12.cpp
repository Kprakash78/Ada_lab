#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lis_dp(const vector<int> &A, vector<int> &sequence) {
    int n = A.size();
    vector<int> dp(n, 1);
    vector<int> parent(n, -1);

    int best_end = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > dp[best_end])
            best_end = i;
    }

    for (int i = best_end; i != -1; i = parent[i])
        sequence.push_back(A[i]);
    reverse(sequence.begin(), sequence.end());

    return dp[best_end];
}

int main() {
    vector<int> A = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 7};

    cout << "Array: ";
    for (int x : A) cout << x << " ";
    cout << "\n";

    vector<int> sequence;
    int len = lis_dp(A, sequence);

    cout << "LIS Length : " << len << "\n";
    cout << "LIS        : ";
    for (int x : sequence) cout << x << " ";
    cout << "\n";

    return 0;
}
