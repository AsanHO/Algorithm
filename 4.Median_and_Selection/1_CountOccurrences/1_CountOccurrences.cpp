#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

void Print(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) cout << arr[i] << " ";
    cout << endl;
}

int Count1(const vector<int>& arr, int x) {
    // TODO: O(n)
    int result = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == x) result++;
    }
    return result;
}

int Count2(vector<int>& arr, int x) {
    int result = 0;
    // TODO: O(log(n) + count)
    int left = 0;
    int right = arr.size() - 1;
    int mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (x > arr[mid]) {
            left = mid + 1;
        } else if (x < arr[mid]) {
            right = mid - 1;
        } else {
            int rmid = mid;
            while (arr[++rmid] == x) {
                result++;
            }
            while (arr[--mid] == x) {
                result++;
            }

            return result + 1;
        }
    }
    return 0;
}

int Count3(const vector<int>& arr, int x) {
    // TODO: O(log(n))
    int left = 0;
    int right = arr.size() - 1;
    int lmid;
    while (left <= right) {  // arr[lmid-1]가 다른 값이어야함
        lmid = (left + right) / 2;
        if (x > arr[lmid]) {
            left = lmid + 1;
        } else if (x < arr[lmid]) {
            right = lmid - 1;
        } else {
            if (arr[lmid - 1] != x) {
                left = 0;
                right = arr.size() - 1;
                int rmid;
                while (left <= right) {  // arr[rmid+1]가 다른 값이어야함
                    rmid = (left + right) / 2;
                    if (x > arr[rmid]) {
                        left = rmid + 1;
                    } else if (x < arr[rmid]) {
                        right = rmid - 1;
                    } else {
                        if (arr[rmid + 1] != x) {
                            break;
                        } else {
                            left = rmid + 1;
                        }
                    }
                }
                return rmid - lmid + 1;
            } else {
                right = lmid - 1;
            }
        }
    }
    return 0;
}

int main() {
    random_device rd;
    mt19937 gen(rd());

    const int n = 20;
    vector<int> my_vector(n);

    int x = 6;  // target to find

    for (int r = 0; r < 100; r++) {
        uniform_int_distribution<int> value_distribution(1, 10);
        generate(my_vector.begin(), my_vector.end(), [&]() { return value_distribution(gen); });
        sort(my_vector.begin(), my_vector.end());

        Print(my_vector);

        const int expected_count = std::count(my_vector.begin(), my_vector.end(), x);

        cout << "Expected count = " << expected_count << endl;

        // 1. O(n) brute force
        if (Count1(my_vector, x) != expected_count) {
            cout << "Wrong count1: " << Count1(my_vector, x) << endl;
            exit(-1);
        }
        sort(my_vector.begin(), my_vector.end());
        // 2. O(log(n) + count)
        if (Count2(my_vector, x) != expected_count) {
            cout << "Wrong count2: " << Count2(my_vector, x) << endl;
            exit(-1);
        }

        // 3. O(log(n))
        if (Count3(my_vector, x) != expected_count) {
            cout << "Wrong count3: " << Count3(my_vector, x) << endl;
            exit(-1);
        }
    }

    cout << "Good!" << endl;

    return 0;
}
