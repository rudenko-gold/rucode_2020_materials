#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <deque>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iomanip>
#include <iterator>
#include <string>
#include <random>

int gcd(int a, int b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a %= b;
        } else {
            std::swap(a, b);
        }
    }
    return a + b;
}

std::vector<int> ans;

void dfs(const int curr, const std::vector<std::vector<int>>& g, std::vector<bool>& visited) {
    visited[curr] = true;
    ans.push_back(curr);
    for (int j: g[curr]) {
        if (!visited[j]) {
            dfs(j, g, visited);
            ans.push_back(curr);
        }
    }
}

int main() {
    int n, d;
    std::cin >> n;

    std::vector<std::pair<int, int>> points;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) {
                if (i == 1)
                    points.emplace_back(1, 1);
                continue;
            }
            d = gcd(i, j);
            if (d == 1) {
                points.emplace_back(i, j);
            }
        }
    }
    int m = points.size();
    std::vector<std::vector<int>> g(m);
    std::vector<bool> visited(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == j)
                continue;
            int x1 = points[i].first, y1 = points[i].second;
            int x2 = points[j].first, y2 = points[j].second;
            if (std::abs(x1 - x2) * std::abs(y1 - y2) == 2) {
                g[i].push_back(j);
            }
        }
    }
    dfs(0, g, visited);
    int check_sum = 0;
    for (bool i: visited) {
        check_sum += i;
    }
    if (check_sum != m) {
        std::cout << -1;
        return 0;
    }
    std::cout << ans.size() << '\n';
    for (auto i: ans) {
        std::cout << points[i].first << " / " << points[i].second << ' ';
    }
}
