#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

const int MAXN = 1000000;
int cnt = 0;
bool used[MAXN];

void dfs(int v, const vector<int>& a) {
    used[v] = true;
    cnt++;

    if (!used[a[v]]) {
        dfs(a[v], a);
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    int max_cycle = 0;
    map<int, int> cycle_len;

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            cnt = 0;
            dfs(i, a);
            max_cycle = max(max_cycle, cnt);
            cycle_len[cnt]++;
        }
    }

    vector<string> ans(n, "No");

    for (int i = 0; i < max_cycle; i++) {
        ans[i] = "Yes";
    }

    for (auto i = cycle_len.begin(); i != cycle_len.end(); ++i) {
        if (i->second > 1 && 2 * i->first < n) {
            ans[i->first * 2 - 1] = "Yes";
        }

        for (auto j = next(i); j != cycle_len.end(); ++j) {
            if (i->first + j->first - 1 < n) {
                ans[i->first + j->first - 1] = "Yes";
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << "\n";
    }

}
