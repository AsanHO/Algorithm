#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

void Print(vector<int>& arr, int start, int end, string sep = "") {
    // cout << "Index: ";
    // for (int i = 0; i < arr.size(); i++)
    //	cout << setfill(' ') << setw(3) << i;
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

int Partition(vector<int>& arr, int start, int end) {
    cout << "Pivot = " << arr[end] << endl;

    int x = arr[end];
    int i = start - 1;
    for (int j = start; j < end; j++)
        if (arr[j] <= x) {
            i += 1;
            swap(arr[i], arr[j]);
        }

    swap(arr[i + 1], arr[end]);

    Print(arr, start, end);

    return i + 1;  // 피벗이 이동한 위치 반환
}

int RandomizedPartition(vector<int>& arr, int start, int end) {
    int random = start + rand() % (end - start + 1);
    swap(arr[random], arr[end]);
    return Partition(arr, start, end);
}

void RandomizedQuicksort(vector<int>& arr, int start, int end) {
    Print(arr, start, end);

    // TODO:
    RandomizedPartition(arr, start, end);
}

int main() {
    srand(2);

    vector<int> arr = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    RandomizedQuicksort(arr, 0, arr.size() - 1);

    Print(arr, 0, arr.size() - 1);

    return 0;
}
