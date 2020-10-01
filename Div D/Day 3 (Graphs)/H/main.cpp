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
int cost[MAXN];

vector<pair<int, int>> graph[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;
    int s = 1, f = n;

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = -1;
        cin >> cost[i];
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;

        graph[from - 1].push_back({to - 1, cost[from - 1]});
        graph[to - 1].push_back({from - 1, cost[to - 1]});
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
        /*
        vector<int> ans;
        for (int v = f - 1; v != -1; v = parent[v]) {
            ans.push_back(v + 1);
        }
        reverse(ans.begin(), ans.end());
        */
        cout << dist[f - 1] << endl;
        /*
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        */
    }
}
