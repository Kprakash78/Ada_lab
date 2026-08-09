#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;

ofstream out;

double linearSearch(vector<int> arr, int key) {
    int n = arr.size();
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            auto end = high_resolution_clock::now();
            return duration<double, nano>(end - start).count();
        }
    }
    auto end = high_resolution_clock::now();
    return duration<double, nano>(end - start).count();
}

int binarySearchHelper(vector<int>& arr, int low, int high, int key) {
    if (low > high)
    { 
        return -1;
    }
    int mid = low + (high - low) / 2;

    if (arr[mid] == key)
    {
        return mid;
    } 
    else if (arr[mid] < key)
    {   
        return binarySearchHelper(arr, mid + 1, high, key);
    }
    else
    { 
        return binarySearchHelper(arr, low, mid - 1, key);
    }
}

double binarySearch(vector<int>& arr, int key) {
    auto start = high_resolution_clock::now();
    binarySearchHelper(arr, 0, (int)arr.size() - 1, key);
    auto end = high_resolution_clock::now();
    return duration<double, nano>(end - start).count();
}


int main() {
    out.open("results2.csv");
    out << "n,algorithm,time_ns\n";
    srand(time(0));

    for (int i = 10; i <= 1000; i++) {

        vector<int> v1;
        while ((int)v1.size() < i) {
            int random_num = rand() % 10000;
            if (find(v1.begin(), v1.end(), random_num) == v1.end()) {
                v1.push_back(random_num);
            }
        }

        vector<int> sortedV1 = v1;
        sort(sortedV1.begin(), sortedV1.end());

        double linearAvg = 0, binaryAvg = 0;
        for (int t = 0; t < 1000; t++) {
            int key = v1[rand() % i];
            linearAvg += linearSearch(v1, key);
            binaryAvg += binarySearch(sortedV1, key);
        }
        linearAvg /= 1000;
        binaryAvg /= 1000;   

        out << i << ",linear,"  << linearAvg << "\n";
        out << i << ",binary,"  << binaryAvg << "\n";

        cout << fixed << setprecision(4);
        cout << "n=" << i << " done\n";
    }

    out.close();
    return 0;
}