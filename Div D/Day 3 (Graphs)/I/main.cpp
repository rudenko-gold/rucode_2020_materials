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
int parent[MAXN];
int cost[MAXN];

vector<pair<int, int>> graph[MAXN];

struct Stop {
    int from, start_time, to, finish_time;
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, from, to, m;
    cin >> n >> from >> to >> m;

    vector<Stop> stops(m);
    vector<int> dist(n, INF);

    dist[from - 1] = 0;

    for (int i = 0; i < m; i++) {
        cin >> stops[i].from >> stops[i].start_time >> stops[i].to >> stops[i].finish_time;
    }

    sort(stops.begin(), stops.end(), [](Stop& left, Stop& right) {
        return left.start_time < right.start_time;
    });

    for (int i = 0; i < m; i++) {
        if (stops[i].start_time >= dist[stops[i].from - 1]) {
            dist[stops[i].to - 1] = min(dist[stops[i].to - 1], stops[i].finish_time);
        }
    }

    if (dist[to - 1] == INF) {
        cout << -1;
    } else {
        cout << dist[to - 1];
    }
}
