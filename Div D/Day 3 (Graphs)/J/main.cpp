#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <queue>
#include <deque>
#include <algorithm>

using namespace std;

const int INF = 1000000000;
const int MAXN = 1000;

int capathity[MAXN][MAXN];
vector<pair<int, int>> graph[MAXN];
int n;

int shortest_path(int cup_cnt) {
    vector<int> dist(n, INF);
    dist[0] = 0;
    vector<bool> used(n, false);

    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || dist[j] < dist[v])) {
                v = j;
            }
        }

        if (dist[v] == INF)
            break;

        used[v] = true;

        for (size_t j = 0; j < graph[v].size(); ++j) {
            int to = graph[v][j].first, w = graph[v][j].second;
            if (dist[v] + w < dist[to] && capathity[v][to] >= cup_cnt) {
                dist[to] = dist[v] + w;
            }
        }
    }

    return dist[n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> n >> m;

    if (n == 1) {
        cout << 10000000 << endl;
        return 0;
    }

    for (int i = 0; i < m; i++) {
        int from, to, w, c;
        cin >> from >> to >> w >> c;

        from--;
        to--;

        c = (c - 3000000) / 100;

        capathity[from][to] = c;
        capathity[to][from] = c;

        graph[from].push_back({to, w});
        graph[to].push_back({from, w});
    }

    int l = 0;
    int r = 10000000;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (shortest_path(mid) <= 1440) {
            l = mid;
        } else {
            r = mid;
        }
    }

    cout << l << endl;
}
