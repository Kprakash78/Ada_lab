#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;
using namespace chrono;

typedef vector<vector<int>> Matrix;

Matrix add(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix sub(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

Matrix naiveMultiplication(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

Matrix strassenRecursive(const Matrix& A, const Matrix& B) {
    int n = A.size();
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int k = n / 2;
    Matrix A11(k, vector<int>(k)), A12(k, vector<int>(k)), A21(k, vector<int>(k)), A22(k, vector<int>(k));
    Matrix B11(k, vector<int>(k)), B12(k, vector<int>(k)), B21(k, vector<int>(k)), B22(k, vector<int>(k));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    Matrix P1 = strassenRecursive(A11, sub(B12, B22));
    Matrix P2 = strassenRecursive(add(A11, A12), B22);
    Matrix P3 = strassenRecursive(add(A21, A22), B11);
    Matrix P4 = strassenRecursive(A22, sub(B21, B11));
    Matrix P5 = strassenRecursive(add(A11, A22), add(B11, B22));
    Matrix P6 = strassenRecursive(sub(A12, A22), add(B21, B22));
    Matrix P7 = strassenRecursive(sub(A11, A21), add(B11, B12));

    Matrix C11 = add(sub(add(P5, P4), P2), P6);
    Matrix C12 = add(P1, P2);
    Matrix C21 = add(P3, P4);
    Matrix C22 = sub(sub(add(P5, P1), P3), P7);

    Matrix C(n, vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
    return C;
}

int nextPowerOf2(int n) {
    int p = 1;
    while (p < n) {
        p *= 2;
    }
    return p;
}

Matrix strassen(const Matrix& A, const Matrix& B) {
    int n = A.size();
    int m = nextPowerOf2(n);

    Matrix A_padded(m, vector<int>(m, 0));
    Matrix B_padded(m, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A_padded[i][j] = A[i][j];
            B_padded[i][j] = B[i][j];
        }
    }

    Matrix C_padded = strassenRecursive(A_padded, B_padded);

    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = C_padded[i][j];
        }
    }
    return C;
}

int main() {
    ofstream out("results7.csv");
    out << "n,algorithm,time_us\n";

    vector<int> ns = {3, 4, 5, 6, 7, 8};
    srand(time(0));

    for (int n : ns) {
        Matrix A(n, vector<int>(n));
        Matrix B(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }

        double naiveTime = 0;
        double strassenTime = 0;
        int iterations = 10000;

        for (int i = 0; i < iterations; i++) {
            auto start1 = high_resolution_clock::now();
            Matrix C1 = naiveMultiplication(A, B);
            auto end1 = high_resolution_clock::now();
            naiveTime += duration<double, micro>(end1 - start1).count();

            auto start2 = high_resolution_clock::now();
            Matrix C2 = strassen(A, B);
            auto end2 = high_resolution_clock::now();
            strassenTime += duration<double, micro>(end2 - start2).count();
        }

        naiveTime /= iterations;
        strassenTime /= iterations;

        out << n << ",naive," << naiveTime << "\n";
        out << n << ",strassen," << strassenTime << "\n";
        cout << "n=" << n << " done\n";
    }

    out.close();
    return 0;
}
