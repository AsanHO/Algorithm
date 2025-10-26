#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>
using namespace std;

void Print(vector<float>& arr) {
    for (auto& a : arr) cout << a << " ";
    cout << endl;
}

void PrintBuckets(vector<vector<float>>& buckets) {
    for (int i = 0; i < buckets.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < buckets[i].size(); j++) cout << buckets[i][j] << " ";
        cout << endl;
    }
}

// 다른 정렬을 사용해도 됩니다.
void InsertionSort(vector<float>& bucket) {
    for (int i = 1; i < bucket.size(); ++i) {
        float key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

void BucketSort(vector<float>& arr, int num_buckets) {
    vector<vector<float>> buckets(num_buckets);

    // TODO:
    for (float num : arr) {
        int hash = (int)(num * 10);
        buckets[hash].push_back(num);
    }

    cout << "Before sorting" << endl;
    PrintBuckets(buckets);

    // TODO:
    for (vector<float>& bucket : buckets) {
        InsertionSort(bucket);
    }

    cout << "After sorting" << endl;
    PrintBuckets(buckets);

    // TODO:
    int i = 0;
    for (vector<float>& bucket : buckets) {
        for (float& num : bucket) {
            arr[i] = num;
            i++;
        }
    }
}

int main() {
    vector<float> arr = {0.78f, 0.17f, 0.39f, 0.26f, 0.72f, 0.94f, 0.21f, 0.12f, 0.23f, 0.67f};

    Print(arr);

    BucketSort(arr, 10);

    Print(arr);

    return 0;
}