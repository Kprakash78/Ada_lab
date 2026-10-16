#include <stdio.h>
#include <stdlib.h>

int longestPalindromeSubsequence(const int a[], int n) {
    if (n == 0) return 0;
    int **dp = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) dp[i] = calloc(n, sizeof(int));
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = dp[i + 1][j] > dp[i][j - 1] ? dp[i + 1][j] : dp[i][j - 1];
            }
        }
    }
    int result = dp[0][n - 1];
    for (int i = 0; i < n; i++) free(dp[i]);
    free(dp);
    return result;
}

int main(void) {
    int a[] = {4, 8, 3, 8, 6, 4, 9, 3, 6, 8, 4, 2, 9, 4, 3, 8, 6, 3, 4, 8, 7, 4, 3, 8, 4};
    int n = sizeof(a) / sizeof(a[0]);
    printf("Longest palindromic subsequence length: %d\n", longestPalindromeSubsequence(a, n));
    return 0;
}