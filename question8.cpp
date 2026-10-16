#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdint>

using namespace std;
using namespace chrono;

struct u128 {
    uint64_t high, low;
    u128(uint64_t h = 0, uint64_t l = 0) : high(h), low(l) {}
    u128(int v) : high(0), low(v) {}
    bool operator==(int v) const { return high == 0 && low == (uint64_t)v; }
};

u128 operator+(u128 a, u128 b) {
    uint64_t low = a.low + b.low;
    uint64_t high = a.high + b.high + (low < a.low);
    return u128(high, low);
}

u128 operator-(u128 a, u128 b) {
    uint64_t low = a.low - b.low;
    uint64_t high = a.high - b.high - (a.low < b.low);
    return u128(high, low);
}

u128 operator<<(u128 a, int shift) {
    if (shift == 0) return a;
    if (shift >= 128) return u128(0, 0);
    if (shift >= 64) return u128(a.low << (shift - 64), 0);
    return u128((a.high << shift) | (a.low >> (64 - shift)), a.low << shift);
}

u128 operator>>(u128 a, int shift) {
    if (shift == 0) return a;
    if (shift >= 128) return u128(0, 0);
    if (shift >= 64) return u128(0, a.high >> (shift - 64));
    return u128(a.high >> shift, (a.low >> shift) | (a.high << (64 - shift)));
}

u128 operator&(u128 a, u128 b) { return u128(a.high & b.high, a.low & b.low); }
u128 operator|(u128 a, u128 b) { return u128(a.high | b.high, a.low | b.low); }
u128 operator^(u128 a, u128 b) { return u128(a.high ^ b.high, a.low ^ b.low); }

u128 mult_by_bit(u128 bit, u128 val) {
    if (bit.low & 1) return val;
    return u128(0, 0);
}

u128 naiveMultiplication(u128 X, u128 Y, int n) {
    u128 P(0, 0);
    for (int i = 0; i < n; i++) {
        if ((Y >> i).low & 1) {
            P = P + (X << i);
        }
    }
    return P;
}

u128 karatsuba(u128 X, u128 Y, int n) {
    if (n <= 1) return u128(0, (X.low & 1) * (Y.low & 1));
    int k = n / 2;
    u128 mask = (u128(0, 1) << k) - u128(0, 1);
    
    u128 X_R = X & mask;
    u128 X_L = (X >> k) & mask;
    u128 Y_R = Y & mask;
    u128 Y_L = (Y >> k) & mask;
    
    u128 P1 = karatsuba(X_L, Y_L, k); 
    u128 P2 = karatsuba(X_R, Y_R, k);
    
    u128 S_X = X_L + X_R;
    u128 S_Y = Y_L + Y_R;
    
    u128 c_X = S_X >> k;
    u128 c_Y = S_Y >> k;
    u128 R_X = S_X & mask;
    u128 R_Y = S_Y & mask;
    
    u128 P3_cross = karatsuba(R_X, R_Y, k);
    u128 P3_part1 = (c_X & c_Y) << (2 * k);
    u128 P3_part2 = (mult_by_bit(c_X, R_Y) + mult_by_bit(c_Y, R_X)) << k;
    
    u128 P3 = P3_part1 + P3_part2 + P3_cross;
    
    return (P1 << (2 * k)) + ((P3 - P1 - P2) << k) + P2;
}

u128 generateRandomNBit(int n) {
    u128 res(0, 0);
    for (int i = 0; i < n; i++) {
        if (rand() % 2) {
            res = res | (u128(0, 1) << i);
        }
    }
    if (n > 0) {
        res = res | (u128(0, 1) << (n - 1));
    }
    return res;
}

int main() {
    ofstream out("results8.csv");
    out << "n,algorithm,time_us\n";

    vector<int> ns = {4, 8, 16, 32, 64};
    srand(time(0));

    u128 dummy(0, 0);

    for (int n : ns) {
        double naiveTime = 0;
        double karatsubaTime = 0;
        int iterations = 100000;

        for (int i = 0; i < iterations; i++) {
            u128 A = generateRandomNBit(n);
            u128 B = generateRandomNBit(n);

            auto start1 = high_resolution_clock::now();
            u128 C1 = naiveMultiplication(A, B, n);
            auto end1 = high_resolution_clock::now();
            naiveTime += duration<double, micro>(end1 - start1).count();

            auto start2 = high_resolution_clock::now();
            u128 C2 = karatsuba(A, B, n);
            auto end2 = high_resolution_clock::now();
            karatsubaTime += duration<double, micro>(end2 - start2).count();

            dummy = dummy ^ C1;
            dummy = dummy ^ C2;
        }

        naiveTime /= iterations;
        karatsubaTime /= iterations;

        out << n << ",naive," << naiveTime << "\n";
        out << n << ",divide_and_conquer," << karatsubaTime << "\n";
        cout << "n=" << n << " done\n";
    }

    out.close();
    
    if (dummy == 1) {
        cout << "";
    }
    return 0;
}
