#include <bits/stdc++.h>
#include <chrono> 

using namespace std::chrono; 
using namespace std;

int partitionArray(int data[], int start, int end) {
    int pivotVal = data[end];
    int smallIdx = start - 1;
    for (int j = start; j < end; j++) {
        if (data[j] < pivotVal) {
            smallIdx++;
            swap(data[smallIdx], data[j]);
        }
    }
    swap(data[smallIdx + 1], data[end]);
    return smallIdx + 1;
}

void quickSortAlgo(int data[], int start, int end) {
    if (start >= end) return;
    int pivot = partitionArray(data, start, end);
    quickSortAlgo(data, start, pivot - 1);
    quickSortAlgo(data, pivot + 1, end);
}

void insertionSortAlgo(int data[], int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        int current = data[i];
        int j = i - 1;
        while (j >= start && data[j] > current) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = current;
    }
}

void hybridSortAlgo(int data[], int start, int end) {
    if (start >= end) return;
    if (end - start + 1 <= 10) {
        insertionSortAlgo(data, start, end);
        return;
    }
    int pivot = partitionArray(data, start, end);
    hybridSortAlgo(data, start, pivot - 1);
    hybridSortAlgo(data, pivot + 1, end);
}

int main() {
    int size = 100000;
    int trials = 10;
    srand(time(0));

    double sumQuickTime = 0;
    double sumHybridTime = 0;

    int arr1[100000];
    int arr2[100000];
    int baseData[100000];

    for (int trial = 1; trial <= trials; trial++) {
        for (int i = 0; i < size; i++) {
            baseData[i] = rand();
        }
        copy(baseData, baseData + size, arr1);
        copy(baseData, baseData + size, arr2);

        auto t1Start = high_resolution_clock::now();
        quickSortAlgo(arr1, 0, size - 1);
        auto t1End = high_resolution_clock::now();
        double quickDuration = duration<double, nano>(t1End - t1Start).count();

        auto t2Start = high_resolution_clock::now();
        hybridSortAlgo(arr2, 0, size - 1);
        auto t2End = high_resolution_clock::now();
        double hybridDuration = duration<double, nano>(t2End - t2Start).count();

        sumQuickTime += quickDuration;
        sumHybridTime += hybridDuration;

        cout << fixed << setprecision(0);
        cout << "Test " << trial << endl;
        cout << "QuickSort: " << quickDuration << endl;
        cout << "Hybrid QuickSort: " << hybridDuration << endl;
        cout << endl;
    }

    double avgQuickTime = sumQuickTime / trials;
    double avgHybridTime = sumHybridTime / trials;

    cout << endl;
    cout << "N = " << size << endl;
    cout << "Average QuickSort Time: " << avgQuickTime << endl;
    cout << "Average Hybrid QuickSort Time: " << avgHybridTime << endl;

    return 0;
}
