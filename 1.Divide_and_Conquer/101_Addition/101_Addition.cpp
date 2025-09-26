#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string Add(string str1, string str2) {
    // TODO: 가장 큰 자리수만큼 반복 std::max 사용
    int max_size = max(str1.size(), str2.size());
    // 뒤의 자리수부터 계산하므로 리버스를 해주고 작은 문자열에는 0으로 패딩을
    // 넣어주자
    /*
    123 -> 321
    012 -> 210
    */
    if (str1.size() != str2.size()) {
        string& isNeed = (str1.size() > str2.size()) ? str2 : str1;
        int target = max_size - isNeed.size();
        for (int i = 0; i < target; i++) {
            isNeed.insert(0, "0");
        }
    }

    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    cout << str1 << endl << str2 << endl;

    /*
    // stoi 문자열을 정수로 변환할 때 사용
        {
                auto i = stoi(string("123")); // stoi("123") 가능
                cout << i * stoi("456") << endl; // 56088
        }
    */
    string result;
    int temp = 0;
    for (int i = 0; i < max_size; i++) {
        int n1 = str1[i] - '0';
        int n2 = str2[i] - '0';
        int sum = n1 + n2 + temp;
        if (sum >= 10) {
            temp = 1;
            sum %= 10;
        } else {
            temp = 0;
        }
        result.append(to_string(sum));
    }
    if (temp == 1) {
        result.append("1");
    }
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    vector<vector<string>> tests = {
        {"12", "34", to_string(12 + 34)},
        {"123", "45", to_string(123 + 45)},
        {"54544", "44545", to_string(54544 + 44545)},
        {"5555", "55", to_string(5555 + 55)},
        {"5555", "5", to_string(5555 + 5)},
        {"5555", "5555", to_string(5555 + 5555)},
        {"9999", "9999", to_string(9999 + 9999)},
        {"9823471235421415454545454545454544",
         "1714546546546545454544548544544545",
         "11538017781967960909090003089999089"}};

    for (const auto& t : tests) {
        const string str1 = t[0];      // "12"
        const string str2 = t[1];      // "34"
        const string expected = t[2];  // "46"

        cout << str1 << " + " << str2 << " = " << expected << endl;

        const string result = Add(str1, str2);

        cout << result << " " << expected << " ";

        if (result == expected)
            cout << "OK" << endl;
        else {
            cout << "Not OK" << endl;
            // exit(-1);
        }
        cout << endl << endl;
    }

    cout << "Congratulations. All OK!" << endl;

    return 0;
}
