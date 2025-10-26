#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>
using namespace std;

void Print(vector<int>& arr) {
    for (auto& a : arr) cout << a << " ";
    cout << endl;
}

// 편의상 결과가 arr에 저장되도록 바꿨습니다.
void CountingSort(vector<int>& arr, int k, int exp) {
    vector<int> temp = arr;  // 복사

    vector<int> count(k + 1, 0);
    // TODO:
    for (int num : arr) {
        count[(num % (exp * 10)) / exp] += 1;
    }
    for (int i = 1; i < k + 1; i++) {
        count[i] += count[i - 1];
    }
    Print(count);
    for (int i = arr.size() - 1; i >= 0; i--) {
        // TODO:
        int expTarget = (temp[i] % (exp * 10)) / exp;
        // cout << "arr[" << count[expTarget] << "] = " << temp[i] << endl;
        arr[count[expTarget] - 1] = temp[i];
        count[expTarget]--;
        Print(count);
        Print(arr);
    }
}

void RadixSort(vector<int>& arr) {
    int k = 9;  // 0 이상 9 이하
    int m = *max_element(arr.begin(), arr.end());

    for (int exp = 1; m / exp > 0; exp *= 10) {
        cout << "exp = " << exp << endl;
        CountingSort(arr, k, exp);
        // Print(arr);
    }
}

int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    // vector<int> arr = {2, 5, 3, 0, 2, 3, 0, 3};

    Print(arr);

    RadixSort(arr);

    return 0;
}