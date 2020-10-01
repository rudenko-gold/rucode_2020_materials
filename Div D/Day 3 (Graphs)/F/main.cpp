#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <queue>
#include <deque>
#include <algorithm>

using namespace std;

const int INF = 1000000000;
const int MAXN = 100000;
bool used[MAXN];
int dist[MAXN];
int parent[MAXN];

vector<pair<int, int>> graph[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s, f;
    cin >> n >> s >> f;

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;
            if (i != j && w != -1) {
                graph[i].push_back({j, w});
            }
        }
    }

    dist[s - 1] = 0;

    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || dist[j] < dist[v])) {
                v = j;
            }
        }

        if (dist[v] == INF) {
            break;
        }

        used[v] = true;

        for (size_t j = 0; j < graph[v].size(); ++j) {
            int to = graph[v][j].first, w = graph[v][j].second;
            if (dist[v] + w < dist[to]) {
                dist[to] = dist[v] + w;
                parent[to] = v;
            }
        }
    }
    if (dist[f - 1] == INF) {
        cout << -1;
    } else {
        cout << dist[f - 1];
    }
}
