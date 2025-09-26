#include <iomanip>  // setfill(), setw()
#include <iostream>
#include <numeric>  // iota
#include <vector>

using namespace std;

void Print(vector<int>& arr, int start, int end) {
    // setfill(), setw()는 줄맞춤에 사용

    for (int i = 0; i < start; i++) cout << "   ";
    for (int i = start; i <= end; i++) cout << setfill(' ') << setw(3) << arr[i];
    cout << endl;
}

bool CheckSorted(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }

    return true;
}

// Sedgewick p. 273
class TopDownMerge {
   public:
    void MergeSort(vector<int>& arr) {
        count = 0;  // 분석용
        aux.resize(arr.size());

        Divide(arr, 0, arr.size() - 1);
    }

   private:
    void Merge(vector<int>& arr, int start, int mid, int end) {
        cout << "Before: ";
        Print(arr, start, end);

        int i = start, j = mid + 1;

        for (int k = start; k <= end; k++) aux[k] = arr[k];

        for (int k = start; k <= end; k++) {
            int target;
            if (i > mid)
                target = aux[j++];
            else if (j > end)
                target = aux[i++];
            else if (aux[j] < aux[i])
                target = aux[j++];
            else
                target = aux[i++];
            arr[k] = target;
        }

        cout << "After : ";
        Print(arr, start, end);

        // count += end - start + 1;
        // cout << "Count : " << end - start + 1 << ", " << count << endl; // 누적 카운트 (디버깅용)
    }

    void Divide(vector<int>& arr, int start, int end) {
        if (end <= start) return;

        int mid = start + (end - start) / 2;

        Divide(arr, start, mid);
        Divide(arr, mid + 1, end);

        Merge(arr, start, mid, end);
    }

    vector<int> aux;  // 추가 메모리 필요
    int count = 0;    // 연산 횟수 세보기용
};

int main() {
    vector<int> my_vector(16);
    std::iota(my_vector.begin(), my_vector.end(), 0);
    std::reverse(my_vector.begin(), my_vector.end());

    cout << "        ";
    Print(my_vector, 0, my_vector.size() - 1);

    TopDownMerge merge;
    merge.MergeSort(my_vector);

    cout << "        ";
    Print(my_vector, 0, my_vector.size() - 1);
}
