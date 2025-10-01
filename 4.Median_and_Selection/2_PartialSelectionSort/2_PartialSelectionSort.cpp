#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

void Print(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) cout << arr[i] << " ";
    cout << endl;
}

// 가장 작은 값이 arr[start]에 오도록
void SelectionSortPass(vector<int>& arr, int start, int end) {
    // TODO:
    int targetIdx = start;
    for (int i = start + 1; i < end; i++) {
        if (arr[i] < arr[targetIdx]) {
            targetIdx = i;
        }
    }
    // int temp = arr[targetIdx];
    // arr[targetIdx] = arr[start];
    // arr[start] = temp;
    swap(arr[start], arr[targetIdx]);
}

void PartialSelectionSort(vector<int>& arr, int k) {
    Print(arr);

    for (int i = 0; i < k; i++) {
        SelectionSortPass(arr, i, arr.size());
        Print(arr);
    }
}

int main() {
    vector<int> my_vector = {7, 10, 4, 3, 20, 15};

    int k = 3;

    PartialSelectionSort(my_vector, k);

    cout << my_vector[k - 1] << endl;
}
