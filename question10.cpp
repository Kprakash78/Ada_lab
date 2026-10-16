#include <bits/stdc++.h>
using namespace std;

void algo1_original(int A[], int n) {
    if (n == 2 && A[0] > A[1]) {
        swap(A[0], A[1]);
    } else if (n > 2) {
        int m = ceil(2.0 * n / 3.0);
        algo1_original(A, m);
        algo1_original(A + n - m, m);
        algo1_original(A, m);
    }
}

void algo1_modified(int A[], int n) {
    if (n == 2 && A[0] > A[1]) {
        swap(A[0], A[1]);
    } else if (n > 2) {
        int m = floor(2.0 * n / 3.0);
        algo1_modified(A, m);
        algo1_modified(A + n - m, m);
        algo1_modified(A, m);
    }
}

int main() {
    int A1[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    int n1 = sizeof(A1) / sizeof(A1[0]);

    int A2[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    int n2 = sizeof(A2) / sizeof(A2[0]);

    cout << "Original Array: ";
    for (int i = 0; i < n1; i++) cout << A1[i] << " ";
    cout << "\n\n";

    algo1_original(A1, n1);
    cout << "After Algo 1 (Original m = ceil(2n/3)): ";
    for (int i = 0; i < n1; i++) cout << A1[i] << " ";
    cout << "\n";

    algo1_modified(A2, n2);
    cout << "After Algo 1 (Modified m = floor(2n/3)): ";
    for (int i = 0; i < n2; i++) cout << A2[i] << " ";
    cout << "\n";

    return 0;
}