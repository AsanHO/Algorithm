#include <iomanip>
#include <iostream>
#include <numeric>  // std::iota
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

// Sedgewick p. 278
class BottomupMerge {
   public:
    void Sort(vector<int>& arr) {
        aux.resize(arr.size());

        int N = arr.size();
        // TODO: 재귀호출 사용하지 않습니다.

        cout << "start" << endl;
        // divide
        //  01 23 45 67 89 1011 1213 1415
        //  0123 4567 891011 12131415
        // =03 47 811 1215
        for (int i = 2; i <= arr.size(); i *= 2) {
            cout << i << "개로 나누기" << endl;
            int startIdx = 0;
            int endIdx = i - 1;
            for (; endIdx < arr.size(); endIdx = startIdx + i - 1) {
                // cout << startIdx << " " << endIdx << endl;
                int midIdx = startIdx + (endIdx - startIdx) / 2;
                Merge(arr, startIdx, midIdx, endIdx);
                startIdx += i;
            }
            cout << endl;
        }
    }

   private:
    void Merge(vector<int>& arr, int start, int mid, int end) {
        // TODO: Top-down과 동일
        // 1. 2개로 시작하며, 2^(n-1)개까지 반복,
        int i = start;
        int j = mid + 1;
        Print(arr, start, end);
        if (arr[mid] <= arr[j]) return;
        for (int i = start; i <= end; i++) {
            aux[i] = arr[i];
        }
        for (int i = start; i <= end; i++) {
            int target;
            if (i > mid)
                target = aux[j++];
            else if (j > end)
                target = aux[i++];
            else if (aux[j] < aux[i])
                target = aux[j++];
            else
                target = aux[i++];
            cout << target;
            arr[i] = target;
        }
        Print(arr, start, end);
    }

    vector<int> aux;  // 추가 메모리
};

int main() {
    vector<int> my_vector(16);
    std::iota(my_vector.begin(), my_vector.end(), 0);
    std::reverse(my_vector.begin(), my_vector.end());

    cout << "        ";
    Print(my_vector, 0, my_vector.size() - 1);

    BottomupMerge merge;
    merge.Sort(my_vector);

    cout << "        ";
    Print(my_vector, 0, my_vector.size() - 1);
}
