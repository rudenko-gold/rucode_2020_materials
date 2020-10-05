#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <map>

using namespace std;

int main() {
    int n, d, w;
    std::cin >> n >> w >> d;
    std::map<int, int> anti;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        anti[a]++;
    }

    std::vector<pair<int, int>> result;
    for (auto& [id, count] : anti) {
        while (count > 0) {
            pair<int, int> p;
            p.first = id;
            if (count >= d) {
                p.second = d;
            } else {
                p.second = count;
            }

            result.emplace_back(p);
            count -= d;
        }
    }

    for (int i = 1; i < result.size(); i++) {
        if (result[i - 1].first == result[i].first) {
            cout << -1;
            return 0;
        }
    }

    if (result.size() > w) {
        std::cout << -1;
    } else {
        for (int i = 0; i < result.size(); ++i) {
            std::cout << result[i].first << ' ';
        }
        std::cout << '\n';
        for (int i = 0; i < result.size(); ++i) {
            std::cout << result[i].second << ' ';
        }
    }
}
