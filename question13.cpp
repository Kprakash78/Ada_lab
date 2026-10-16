#include <bits/stdc++.h>
using namespace std;

int longestAlternating( vector<int>& a) {
    int n = a.size();
    int up = 1, down = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            down = up + 1;
        } else if (a[i] > a[i - 1] && down > 0) {
            up = down + 1;
        }
    }
    return max(up, down);
}

int main() {
    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 7};
    cout << longestAlternating(a) << "\n";
}