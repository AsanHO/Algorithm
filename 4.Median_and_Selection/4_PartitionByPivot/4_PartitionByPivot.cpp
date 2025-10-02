#include <iostream>
#include <vector>
using namespace std;

void Print(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    // vector<int> arr = {5, 2, 7, 3, 8, 5, 6, 4};
    /*
    5 2 7 3 8 5 6 4
    i = -1, j = 0
    5 2 7 3 8 5 6 4
    i = 0, j = 1
    2 5 7 3 8 5 6 4
    i = 0, j = 2
    2 5 7 3 8 5 6 4
    i = 1, j = 3
    2 3 7 5 8 5 6 4
    i = 1, j = 4
    2 3 7 5 8 5 6 4
    i = 1, j = 5
    2 3 7 5 8 5 6 4
    i = 1, j = 6
    2 3 7 5 8 5 6 4
    2 3 4 5 8 5 6 7
    2 // <- 인덱스 2 + 1 = 3이 피벗의 마지막 위치
    */
    // vector<int> arr = {2, 8, 7, 1, 3, 5, 6, 4};
    // vector<int> arr = {9, 8, 7, 6, 4, 3, 2, 1, 5};
    vector<int> arr = {5, 2, 7, 3, 4, 4, 6, 4};

    int lo = 0;               // 첫 인덱스
    int hi = arr.size() - 1;  // 마지막 인덱스
    int x = arr[hi];          // 분할 기준으로 사용하는 pivot 4

    int i = lo - 1;  // pivot보다 작은 것들중 가장 큰 인덱스

    Print(arr);

    // TODO:
    for (int j = 0; j < hi; j++) {
        if (arr[j] <= x) {
            i++;
            swap(arr[j], arr[i]);
        }
        Print(arr);
    }

    swap(arr[i + 1], arr[hi]);
    Print(arr);

    cout << i + 1 << endl;  // 피벗 이하인 값들의 마지막 인덱스
}
