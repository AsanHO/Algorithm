#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

void Print(vector<int>& arr, int start, int end, string sep = "") {
    // cout << "Index: ";
    // for (int i = 0; i < arr.size(); i++) cout << setfill(' ') << setw(3) << i;
    // cout << endl;

    cout << "Value: ";
    for (int i = 0; i < arr.size(); i++) {
        if (start <= i && i <= end)
            cout << setfill(' ') << setw(3) << arr[i] << sep;
        else
            cout << "   ";
    }
    cout << endl;
}

// Quicksort with 3-way partitioning, Sedgewick p299
// (Dijkstra's Dutch national flag problem)
/*
1.Key보다 작은 값들,
2.key와 같은 값들,
3.key 보다 큰 값들
*/
void Quick3way(vector<int>& arr, int start, int end) {
    // cout << start << ":" << end << endl;

    if (end <= start) return;

    int lt = start, i = start + 1, gt = end;
    int key = arr[start];  // pivot
    cout << "Key = " << key << endl;
    while (i <= gt) {
        cout << lt << " " << i << " " << gt << endl;
        if (arr[i] < key) {  // 작을때,
            swap(arr[i], arr[lt]);
            lt++;
            i++;
        } else if (arr[i] == key) {  // 같을때
            i++;
        } else {  // 클때
            swap(arr[i], arr[gt]);
            gt--;
        }
        Print(arr, start, end);
    }

    Quick3way(arr, start, lt - 1);
    Quick3way(arr, gt + 1, end);
}

int main() {
    srand(0);

    vector<int> arr = {3, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 2, 3, 4, 5, 1, 3, 5};

    Print(arr, 0, arr.size() - 1);

    Quick3way(arr, 0, arr.size() - 1);

    Print(arr, 0, arr.size() - 1);

    return 0;
}
