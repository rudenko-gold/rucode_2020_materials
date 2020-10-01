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

void dfs(int v) {
    used[v] = true;

    for (int i = 0; i < graph[v].size(); ++i) {
        if (!used[graph[v][i]]) {
            dfs(graph[v][i]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int from = 0; from < n; from++) {
        int to;
        cin >> to;
        graph[to - 1].push_back(from);
        graph[from].push_back(to - 1);
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
            ans++;
        }
    }
    cout << ans;
}
