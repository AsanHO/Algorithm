#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
string Add(string str1, string str2);
string singleMultiply(string str, char target);
string Multiply(string str1, string str2) {
    // TODO:

    string result;
    reverse(str2.begin(), str2.end());
    for (int i = 0; i < str2.size(); i++) {
        string miniresult = singleMultiply(str1, str2[i]);
        for (int j = 0; j < i; j++) {
            miniresult += "0";
        }
        // cout << miniresult << endl;
        result = Add(result, miniresult);
    }

    return result;
}

string singleMultiply(string str, char target) {
    // TODO:
    // cout << "singleMultiply(" << str << "," << target << ")" << endl;
    string result;
    reverse(str.begin(), str.end());
    for (int i = 0; i < str.size(); i++) {
        // cout << str[i] - '0' << target - '0' << endl;
        string miniResult = to_string(((str[i] - '0') * (target - '0')));
        // cout << "miniResult : " << miniResult << endl;
        for (int j = 0; j < i; j++) {
            miniResult += "0";
        }
        result = Add(result, miniResult);
        // cout << "result : " << result << endl;
    }
    // cout << "result : " << result << endl;
    return result;
}

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
        {"12", "34", std::to_string(12 * 34)},
        {"123", "45", std::to_string(123 * 45)},
        {"5555", "55", std::to_string(5555 * 55)},
        {"5555", "5555", std::to_string(5555 * 5555)},
        {"98234712354214154", "171454654654655",
         "16842798681791158832220782986870"}
        // , {"9823471235421415454545454545454544",
        // "1714546546546545454544548544544545",
        // "16842798681791114273590624445460185389471221520083884298838480662480"}
    };

    for (const auto& t : tests) {
        const string str1 = t[0];
        const string str2 = t[1];
        const string expected = t[2];

        cout << str1 << " * " << str2 << " = " << expected << endl;

        const string result = Multiply(str1, str2);

        cout << result << " " << expected << " ";

        if (result == expected)
            cout << "OK";
        else {
            cout << "Not OK";
            exit(-1);
        }
        cout << endl << endl;
    }

    cout << "Congratulations. All OK!" << endl;

    return 0;
}
