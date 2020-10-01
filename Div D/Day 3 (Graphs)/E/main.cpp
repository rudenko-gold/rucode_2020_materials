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

vector<pair<int, int>> graph[MAXN];

int n;
int k = 10;

vector<queue<int>> queues;;

int dist[MAXN];
bool used[MAXN];

int shortest_path(int from, int to) {
    fill(dist, dist + n, MAXN);
    fill(used, used + n, false);

    dist[from] = 0;
    queues[0].push(from);

    for (int i = 0; i < queues.size(); i++) {
        queue<int>& q = queues[i];

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            if (used[v]) {
                continue;
            }

            used[v] = true;
            dist[v] = i;

            for (int j = 0; j < graph[v].size(); j++) {
                int next = graph[v][j].first;
                int w = graph[v][j].second;

                if (!used[next]) {
                    queues[i + w].push(next);
                }
            }
        }
    }

    return dist[to];
}

struct Edge {
    int from, to, w;
};

void delete_edge(int from, int to, int w) {
    for (int i = 0; i < graph[from].size(); i++) {
        if (graph[from][i].first == to && graph[from][i].second == w) {
            swap(graph[from][i], graph[from].back());
            graph[from].pop_back();
        }
    }
}

void insert_edge(int from, int to, int w) {
    graph[from].push_back({to, w});
    graph[to].push_back({from, w });
}

void print_graph() {
    for (int i = 0; i < n; i++) {
        cerr << i << " | ";
        for (int j = 0; j < graph[i].size(); ++j) {
            cerr << "(" << graph[i][j].first << ", " << graph[i][j].second << ") " ;
        }
        cerr << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> n >> m;
    queues.resize((n - 1) * k + 1);
    vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        int from, to, w;
        cin >> from >> to >> w;

        from--;
        to--;

        insert_edge(from, to, w);

        edges[i] = { from, to, w };
    }


    int ans = INF;

    for (int i = 0; i < m; i++) {
        delete_edge(edges[i].from, edges[i].to, edges[i].w);
        delete_edge(edges[i].to, edges[i].from, edges[i].w);

        int path = shortest_path(edges[i].from, edges[i].to);

        ans = min(ans, path + edges[i].w);
        insert_edge(edges[i].from, edges[i].to, edges[i].w);
    }

    if (ans == INF) {
        cout << -1;
    } else {
        cout << ans;
    }
}
