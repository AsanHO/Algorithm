#include <iostream>
#include <vector>
using namespace std;
void print(vector<int> &arr) {
    for (auto num : arr) {
        cout << num << " ";
    }
    cout << endl;
}
int main() {
    vector<int> arr = {8, 2, 3, 5, 9, 1, 9, 4, 3, 7, 6, 7};

    // TODO:
    if (arr[0] > arr[1]) swap(arr[0], arr[1]);
    print(arr);
    for (int i = 2; i < arr.size(); i += 2) {
        if (arr[i] > arr[i + 1]) swap(arr[i], arr[i + 1]);

        arr[0] = std::min(arr[i], arr[0]);      // min() 내부에서 비교 1번
        arr[1] = std::max(arr[i + 1], arr[1]);  // max() 내부에서 비교 1번
        print(arr);
    }
    cout << "Min value = " << arr[0] << ", Max value = " << arr[1] << endl;  // Min value = 1, Max value = 9
}
