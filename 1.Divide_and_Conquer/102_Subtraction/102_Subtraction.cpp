#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 항상 큰 수에서 작은 수를 빼는 경우(결과가 음수가 되지 않는 경우)를 가정
string Subtract(string str1, string str2) {
    // 둘이 같을 경우 바로 "0" 반환
    if (str1 == str2) return "0";  // '0'은 char, "0"은 string

    int N = max(str1.size(), str2.size());
    str1 = string(N - str1.size(), '0') + str1;  // 문자열끼리의 더하기도 가능
    str2 = string(N - str2.size(), '0') + str2;

    string result;
    cout << "str1 :" << str1 << endl;
    cout << "str2 :" << str2 << endl;
    cout << "result :" << result << endl;
    // TODO: 더하기와 거의 비슷합니다.
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int temp = 0;
    for (int i = 0; i < N; i++) {
        int n1 = str1[i] - '0';
        int n2 = str2[i] - '0';
        int sum = n1 - n2 - temp;
        if (sum < 0) {
            temp = 1;
            sum += 10;
        } else {
            temp = 0;
        }
        result.append(to_string(sum));
    }
    // 불필요한 '0' 제거 (예: "078" -> "78")
    // TODO:
    reverse(result.begin(), result.end());
    for (int i = 0; result[i] == '0'; i++) {
        result.erase(result.begin());
    }

    return result;
}

int main() {
    // 항상 큰 수에서 작은 수를 빼는 경우(결과가 음수가 되지 않는 경우)를 가정
    vector<vector<string>> tests = {
        {"34", "12", std::to_string(34 - 12)},
        {"123", "45", std::to_string(123 - 45)},
        {"54544", "44545", std::to_string(54544 - 44545)},
        {"5555", "55", std::to_string(5555 - 55)},
        {"5555", "5555", std::to_string(5555 - 5555)},
        {"9823471235421415454545454545454544",
         "1714546546546545454544548544544545",
         "8108924688874870000000906000909999"}};

    for (const auto& t : tests) {
        const string str1 = t[0];
        const string str2 = t[1];
        const string expected = t[2];

        cout << str1 << " - " << str2 << " = " << expected << endl;

        const string result = Subtract(str1, str2);

        cout << result << " " << expected << " ";

        if (result == expected)
            cout << "OK";
        else {
            cout << "Not OK";
            // exit(-1);
        }
        cout << endl << endl;
    }

    cout << "Congratulations. All OK!" << endl;

    return 0;
}
