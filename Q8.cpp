#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <climits>

using namespace std;
using namespace chrono;

typedef unsigned long long ull;

ull naiveMultiply(ull num1, ull num2, int totalBits) {
    ull ans = 0;
    for (int i = 0; i < totalBits; i++) {
        if ((num2 >> i) & 1)
            ans += (num1 << i);
    }
    return ans;
}

ull karatsubaMultiply(ull num1, ull num2, int totalBits) {
    if (totalBits <= 2)
        return num1 * num2;

    int splitAt = totalBits / 2;
    ull lowerMask = ((ull)1 << splitAt) - 1;

    ull firstLow  = num1 & lowerMask;
    ull firstHigh = num1 >> splitAt;
    ull secondLow  = num2 & lowerMask;
    ull secondHigh = num2 >> splitAt;

    ull prod0 = karatsubaMultiply(firstLow, secondLow, splitAt);
    ull prod2 = karatsubaMultiply(firstHigh, secondHigh, splitAt);
    ull prod1 = karatsubaMultiply(firstLow + firstHigh, secondLow + secondHigh, splitAt + 1) - prod2 - prod0;

    return (prod2 << (2 * splitAt)) + (prod1 << splitAt) + prod0;
}

int main() {
    srand(time(0));

    int nValues[] = {4, 8, 16, 32, 64};
    int numCases = 5;
    int iterations = 100000;

    ofstream outputFile("Q8_results.csv");
    outputFile << "N,Naive_ns,Karatsuba_ns\n";

    for (int idx = 0; idx < numCases; idx++) {
        int n = nValues[idx];

        ull upperLimit = (n == 64) ? ULLONG_MAX : ((ull)1 << n) - 1;
        ull num1 = ((ull)rand() ^ ((ull)rand() << 15)) & upperLimit;
        ull num2 = ((ull)rand() ^ ((ull)rand() << 15)) & upperLimit;

        volatile ull checksum = 0;

        auto naiveStart = high_resolution_clock::now();
        for (int r = 0; r < iterations; r++)
            checksum ^= naiveMultiply(num1, num2, n);
        auto naiveEnd = high_resolution_clock::now();
        double timeTakenNaive = duration<double, nano>(naiveEnd - naiveStart).count() / iterations;

        auto karatStart = high_resolution_clock::now();
        for (int r = 0; r < iterations; r++)
            checksum ^= karatsubaMultiply(num1, num2, n);
        auto karatEnd = high_resolution_clock::now();
        double timeTakenKaratsuba = duration<double, nano>(karatEnd - karatStart).count() / iterations;

        cout << "N = " << n << " bits" << endl;
        cout << "Naive Time     : " << timeTakenNaive << " ns" << endl;
        cout << "Karatsuba Time : " << timeTakenKaratsuba << " ns" << endl;
        cout << endl;

        outputFile << n << "," << timeTakenNaive << "," << timeTakenKaratsuba << "\n";
    }

    outputFile.close();
    return 0;
}
