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

vector<int> graph[MAXN];
bool v_type[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;
        v_type[i] = type - 1;
        parent[i] = -1;
        dist[i] = INF;
    }

    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    dist[0] = 0;
    deque<int> d;
    d.push_back(0);

    while (!d.empty()) {
        int v = d.front();
        d.pop_front();

        for (int i = 0; i < graph[v].size(); ++i) {
            int to = graph[v][i];
            int w = v_type[v] == v_type[to] ? 0 : 1;

            if (dist[to] > dist[v] + w) {
                dist[to] = dist[v] + w;
                parent[to] = v;
                if (w == 0) {
                    d.push_front(to);
                } else {
                    d.push_back(to);
                }
            }
        }
    }

    if (dist[n - 1] == INF) {
        cout << "impossible";
    } else {
        vector<int> ans;
        for (int v = n - 1; v != -1; v = parent[v]) {
            ans.push_back(v + 1);
        }
        reverse(ans.begin(), ans.end());

        cout << dist[n - 1] << " " << ans.size() << "\n";
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
    }
}
