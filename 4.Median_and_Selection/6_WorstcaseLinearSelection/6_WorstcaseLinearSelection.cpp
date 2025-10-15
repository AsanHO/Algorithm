#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>
using namespace std;

void Print(vector<int>& arr, int start, int end, string sep = "") {
    cout << "Index: ";
    for (int i = 0; i < arr.size(); i++) cout << setfill(' ') << setw(3) << i;
    cout << endl;

    cout << "Value: ";
    for (int i = 0; i < arr.size(); i++) {
        if (start <= i && i <= end)
            cout << setfill(' ') << setw(3) << arr[i] << sep;
        else
            cout << "   ";
    }
    cout << endl;
}

// 그룹 단위로 출력 (그룹 단위 정렬 확인용)
void PrintGroups(vector<int>& arr, int start, int g) {
    for (int j = start; j <= start + g - 1; j++) {
        cout << "Group " << j - start + 1 << " : ";
        for (int l = 0; l < 5; l++) cout << arr[j + l * g] << " ";
        cout << endl;
    }
}

int Partition(vector<int>& arr, int start, int end) {
    int x = arr[end];
    int i = start - 1;
    for (int j = start; j < end; j++)
        if (arr[j] <= x) {
            i += 1;
            swap(arr[i], arr[j]);
        }
    swap(arr[i + 1], arr[end]);
    return i + 1;  // 피벗이 이동한 위치 반환
}

// 선택정렬의 안쪽루프, stride 확인해보세요.
void SelectionSortPass(vector<int>& arr, int start, int end, int stride = 1) {
    int min_index = start;
    for (int j = start + stride; j <= end; j += stride)
        if (arr[j] < arr[min_index]) min_index = j;
    swap(arr[start], arr[min_index]);
}

// 구현 편의상 Select()가 값과 인덱스를 같이 반환
struct Pair {
    int index;
    int value;
};

// CLRS 9.3
Pair Select(vector<int>& arr, int start, int end, int mid) {
    cout << "n = " << end - start + 1 << ", start = " << start << ", end = " << end << ", mid = " << mid << endl;
    Print(arr, start, end);

    // 5로 나눠서 떨어지지 않는 경우에는 정렬해서 범위를 줄이기
    while ((end - start + 1) % 5 != 0) {
        SelectionSortPass(arr, start, end);
        if (mid == 1) return {start, arr[start]};
        start += 1;
        mid -= 1;
    }

    int g = (end - start + 1) / 5;  // 그룹의 개수

    // 그룹단위 정렬 전 출력
    PrintGroups(arr, start, g);

    // TODO: 각각의 그룹 정렬(힌트: stride 사용)
    for (int i = start; i < end; i++) {
        SelectionSortPass(arr, i, end, g);
    }

    cout << "sorted...." << endl;
    // 그룹단위 정렬 후 출력
    PrintGroups(arr, start, g);

    // 가운데 몰려있는 그룹별 중간값들에 대해 재귀 호출
    Pair x = Select(arr, start + 2 * g, start + 3 * g - 1, std::ceil(g / 2.0));

    cout << "start = " << start << ", end = " << end << ", Median of medians = " << x.value << endl;

    // 중간값들의 중간값을 피벗으로 사용
    swap(arr[x.index], arr[end]);

    int index = Partition(arr, start, end);

    if (index - start == mid - 1)
        return Pair{index, arr[index]};
    else if (mid - 1 < index - start)
        return Select(arr, start, index - 1, mid);
    else
        return Select(arr, index + 1, end, mid - index + start - 1);
}

int SelectionBySorting(vector<int> arr, int mid)  // arr은 사본
{
    std::sort(arr.begin(), arr.end());
    return arr[mid - 1];
}

struct Sample {
    int n;
    double duration;
};

int main() {
    // vector<int> my_vector = {11, 7, 14, 6, 20, 4, 0, 10, 23, 5, 8, 17, 9, 21, 12, 22, 19, 15, 3, 13, 18, 1, 2, 16};
    vector<int> my_vector(25);
    std::iota(my_vector.begin(), my_vector.end(), 0);  // iota는 0, 1, 2, ... , n-1 까지 순서대로 채워주는 함수
    std::reverse(my_vector.begin(), my_vector.end());

    cout << "Median = " << Select(my_vector, 0, my_vector.size() - 1, std::ceil(my_vector.size() / 2.0)).value << endl;

    return 0;

    // random_device rd;
    // mt19937 gen(rd());

    // vector<Sample> samples;
    // samples.reserve(5000);

    // for (int n = 1; n <= 10000; n += 1)
    //{
    //	vector<int> my_vector(n);

    //	uniform_int_distribution<int> value_distribution(0, (n - 1) / 2); // 중복 발생
    //	generate(my_vector.begin(), my_vector.end(), [&]() { return value_distribution(gen); });
    //	//std::iota(my_vector.begin(), my_vector.end(), 0); // iota는 0, 1, 2, ... , n-1 까지 순서대로 채워주는 함수
    //	//std::random_shuffle(my_vector.begin(), my_vector.end()); // 일부만 순서를 바꿔줌 (shuffle은 딜러가 카드 섞는 것 생각하면 됩니다.)
    //	//std::reverse(my_vector.begin(), my_vector.end());

    //	vector<int> backup = my_vector;

    //	int mid = int(my_vector.size() / 2) + 1;
    //	int expected_value = SelectionBySorting(my_vector, mid);
    //	int selected_value = Select(my_vector, 0, my_vector.size() - 1, mid).value;

    //	// Print(my_vector, 0, my_vector.size() - 1);
    //	// cout << expected_value << " " << selected_value << endl;

    //	if (expected_value != selected_value)
    //	{
    //		cout << "Incorrect. " << expected_value << " " << selected_value << endl;

    //		Print(backup, 0, backup.size(), ",");

    //		Print(my_vector, 0, my_vector.size() - 1);
    //		exit(-1);
    //	}
    //}

    // cout << "Good!" << endl;
}