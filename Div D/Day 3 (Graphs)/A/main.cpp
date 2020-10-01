#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

const int INF = 1000000000;

bool used[1000][1000];
bool table[1000][1000];
int dist[1000][1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> table[i][j];
            dist[i][j] = INF;
        }
    }

    int x_s, y_s, x_f, y_f;
    cin >> x_s >> y_s >> x_f >> y_f;
    x_s--;
    x_f--;
    y_s--;
    y_f--;

    queue<pair<int, int>> q;
    q.push({y_s, x_s});
    used[y_s][x_s] = true;
    dist[y_s][x_s] = 0;

    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();

        int i = p.first;
        int j = p.second;
        //cerr << i << " " << j << "  " << dist[i][j] << endl ;
        if (i != 0 && table[i - 1][j] != 1 && !used[i - 1][j]) {
            used[i - 1][j] = true;
            dist[i - 1][j] = dist[i][j] + 1;
            q.push({i - 1, j});
        }
        if (j != 0 && table[i][j - 1] != 1 && !used[i][j - 1]) {
            used[i][j - 1] = true;
            dist[i][j - 1] = dist[i][j] + 1;
            q.push({i, j - 1});
        }
        if (j != m - 1 && table[i][j + 1] != 1 && !used[i][j + 1]) {
            dist[i][j + 1] = dist[i][j] + 1;
            used[i][j + 1] = true;
            q.push({i, j + 1});
        }
        if (i != n - 1 && table[i + 1][j] != 1 && !used[i + 1][j]) {
            dist[i + 1][j] = dist[i][j] + 1;
            used[i + 1][j] = true;
            q.push({i + 1, j});
        }
    }

    if (dist[y_f][x_f] == INF) {
        cout << -1;
    } else {
        cout << dist[y_f][x_f];
    }
}
