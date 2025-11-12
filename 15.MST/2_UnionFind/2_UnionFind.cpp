#include <utility>

#include "UnionFind.h"
using namespace std;

int main() {
    UnionFind uf(4);
    vector<pair<int, int>> tests = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 2}};

    uf.Print();

    for (auto t : tests) {
        int u = t.first;
        int v = t.second;
        bool connected = uf.Connected(u, v);  // uf.Find(p) == uf.Find(q);

        cout << u << " " << v << " " << std::boolalpha << connected << endl;
        cout << "Union " << u << " " << v << endl;

        uf.Union(u, v);

        uf.Print();
    }
}
/*
// Quick-Find 방식
Num groups = 4
Index:  0  1  2  3
Group:  0  1  2  3
0 1 false
Union 0 1           // 0과 1을 같은 그룹으로 합침
Num groups = 3
Index:  0  1  2  3
Group:  1  1  2  3  // 0과 1 둘 다 그룹 번호가 1번
1 2 false
Union 1 2
Num groups = 2
Index:  0  1  2  3
Group:  2  2  2  3  // {0, 1, 2}는 같은 그룹 (2번)
2 3 false
Union 2 3
Num groups = 1
Index:  0  1  2  3
Group:  3  3  3  3  // 2와 3을 합치면서 모두 같은 그룹 (3번)
3 0 true
Union 3 0
Num groups = 1
Index:  0  1  2  3
Group:  3  3  3  3


// Quick-Union 방식
Num groups = 4
Index:  0  1  2  3
Group:  0  1  2  3 // 처음에는 모두 다른 그룹, index와 Group[index]가 같다
0 1 false
Union 0 1
Num groups = 3
Index:  0  1  2  3
Group:  1  1  2  3 // 0과 1이 둘 다 Group 1이라고 기록
1 2 false
Union 1 2
Num groups = 2
Index:  0  1  2  3
Group:  1  2  2  3 // {0, 1, 2}가 모두 같은 그룹인데 숫자가 다릅니다.

Union()할 때는 최소한으로 두 개가 연결되었다는 것만 기록합니다.
Find() 할 때 0은 1이랑 연결되었네, 1은 2랑 연결되었네, ... , 같이 찾아가는 방식입니다.
인덱스 0은 1과 같은 그룹이라는 의미에서 Group[1]
Group[Group[1]] = Group[2] 가 2라는 것은 1이 2와 연결되었다는 의미
Group[Group[Group[1]]] = Group[Group[2]] = Group[2] = 2
인덱스 2와 그룹 번호 2가 같으니까 여기까지가 같은 그룹이라는 의미
그래서 0, 1, 2가 같은 그룹이라고 확인하는 방식 (족보에서 조상이 누구인지 찾아가는 느낌입니다.)
2 3 false
Union 2 3
Num groups = 1
Index:  0  1  2  3
Group:  1  2  3  3
3 0 true
Union 3 0
Num groups = 1
Index:  0  1  2  3
Group:  1  2  3  3
*/
