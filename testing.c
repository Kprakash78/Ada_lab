#include <stdio.h>
#include <limits.h>

int m[100][100], s[100][100], d[100];

void printOrder(int i, int j) {
    if (i == j) {
        printf("M%d", i);
        return;
    }
    printf("(");
    printOrder(i, s[i][j]);
    printOrder(s[i][j] + 1, j);
    printf(")");
}

int main() {
    int n;
    printf("Enter number of matrices n: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    printf("Enter %d dimensions (d0 d1 ... dn): ", n + 1);
    fflush(stdout);
    for (int i = 0; i <= n; i++) {
        if (scanf("%d", &d[i]) != 1) {
            return 0;
        }
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i + L - 1 <= n; i++) {
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

    printf("\nMinimum Multiplications: %d\n", m[1][n]);
    printf("Optimal Parenthesization: ");
    printOrder(1, n);
    printf("\n");
    return 0;
}