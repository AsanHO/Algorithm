// birthday_simulation.cpp
// 23명중에 생일이 같을 확률은 무려 50퍼센트 이상이다.
// => 해싱에서 충돌은 굉장히 많이 일어난다.
// 간단한 몬테카를로 시뮬레이션으로 "같은 생일을 가진 사람이 있는지"를 확인합니다.
// 컴파일: g++ -std=c++11 -O2 birthday_simulation.cpp -o birthday_sim
// 실행 예: ./birthday_sim 23 100000

#include <chrono>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

int main(int argc, char** argv) {
    int group_size = 23;
    long long trials = 100000;  // 기본 시도 횟수

    if (argc >= 2) group_size = std::stoi(argv[1]);
    if (argc >= 3) trials = std::stoll(argv[2]);

    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<int> dist(1, 365);

    long long success = 0;  // 적어도 한 쌍이 같은 생일인 실험 수

    for (long long t = 0; t < trials; ++t) {
        std::unordered_set<int> seen;
        seen.reserve(group_size * 2);
        bool found = false;

        for (int i = 0; i < group_size; ++i) {
            int b = dist(rng);
            if (seen.find(b) != seen.end()) {
                found = true;
                break;
            }
            seen.insert(b);
        }

        if (found) ++success;
    }

    double prob = (double)success / (double)trials;

    std::cout << "Group size: " << group_size << "\n";
    std::cout << "Trials: " << trials << "\n";
    std::cout << "Simulated probability (>=1 matching pair): " << prob << "\n";
    std::cout << "Matches: " << success << " / " << trials << "\n";

    return 0;
}
