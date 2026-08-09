#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;

ofstream out;

double bubbleSort(vector<int> arr) {
    int n = arr.size();
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    auto end = high_resolution_clock::now();
    return duration<double, micro>(end - start).count();
}

double selectionSort(vector<int> arr) {
    int n = arr.size();
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        swap(arr[i], arr[minIndex]);
    }
    auto end = high_resolution_clock::now();
    return duration<double, micro>(end - start).count();
}

double insertionSort(vector<int> arr) {
    int n = arr.size();
    auto start = high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
    auto end = high_resolution_clock::now();
    return duration<double, micro>(end - start).count();
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

double quickSort(vector<int> arr) {
    auto start = high_resolution_clock::now();
    if (!arr.empty()) {
        quickSortHelper(arr, 0, arr.size() - 1);
    }
    auto end = high_resolution_clock::now();
    return duration<double, micro>(end - start).count();
}

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;

    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < L.size())
        arr[k++] = L[i++];

    while (j < R.size())
        arr[k++] = R[j++];
}

void mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

double mergeSort(vector<int> arr) {
    auto start = high_resolution_clock::now();
    if (!arr.empty()) {
        mergeSortHelper(arr, 0, arr.size() - 1);
    }
    auto end = high_resolution_clock::now();
    return duration<double, micro>(end - start).count();
}

int main() {
    out.open("results.csv");
    out << "n,algorithm,time_us\n";
    srand(time(0));

    for (int i = 10; i <= 1000; i++) {
        vector<int> v1;

        while ((int)v1.size() < i) {
            int random_num = rand() % 10000;
            if (find(v1.begin(), v1.end(), random_num) == v1.end()) {
                v1.push_back(random_num);
            }
        }

        double bubbleAvg = 0, selectionAvg = 0, insertionAvg = 0, quickAvg = 0, mergeAvg = 0;
        for (int t = 0; t < 10; t++) {
            bubbleAvg    += bubbleSort(v1);
            selectionAvg += selectionSort(v1);
            insertionAvg += insertionSort(v1);
            quickAvg     += quickSort(v1);
            mergeAvg     += mergeSort(v1);
        }
        bubbleAvg /= 10; selectionAvg /= 10; insertionAvg /= 10; quickAvg /= 10; mergeAvg /= 10;

        out << i << ",bubble,"     << bubbleAvg    << "\n";
        out << i << ",selection," << selectionAvg << "\n";
        out << i << ",insertion," << insertionAvg << "\n";
        out << i << ",quicksort," << quickAvg     << "\n";
        out << i << ",mergesort," << mergeAvg     << "\n";

        cout << fixed << setprecision(4);
        cout << "n=" << i << " done\n";
    }

    out.close();
    return 0;
}