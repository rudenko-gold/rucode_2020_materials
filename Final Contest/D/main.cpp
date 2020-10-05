#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main() {
    int n, s;
    cin >> n >> s;

    vector<int> a(n);
    vector<int> parent(n, -1);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> dp(n);
    int ans = 0;
    int ans_idx = 0;
    for (int i = 0; i < n; ++i) {
        dp[i] = 1;

        for (int j = 0; j < i; ++j) {
            if (a[i] >= a[j] && a[i] - a[j] <= s) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
        }

        if (dp[i] > dp[ans_idx]) {
            ans_idx = i;
        }
    }


    vector<int> ans_v;
    unordered_set<int> se;
    for (int i = ans_idx; i != -1; i = parent[i]) {
        se.insert(i);
    }

    cout << dp[ans_idx] << "\n";
    for (int i = 0; i < n; i++) {
        cout << (se.find(i) != se.end()) << " ";
    }

    return 0;
}
