#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

struct Gangster {
    int t, p, s;
};

int main() {
    int n, k, t;
    cin >> n >> k >> t;
    vector<Gangster> g(n);

    for (int i = 0; i < n; i++) {
        cin >> g[i].t;
    }

    for (int i = 0; i < n; i++) {
        cin >> g[i].p;
    }

    for (int i = 0; i < n; i++) {
        cin >> g[i].s;
    }

    sort(g.begin(), g.end(), [](Gangster& lhs, Gangster& rhs) {
        return lhs.t < rhs.t;
    });
    
    vector<int> dp(n + 1, -1);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (g[i - 1].t >= g[i - 1].s) {
            dp[i] = g[i - 1].p;
        }

        for (int j = 1; j < i; j++) {
            if (g[i - 1].t - g[j - 1].t >= abs(g[i - 1].s - g[j - 1].s) && dp[j] != -1) {
                dp[i] = max(dp[i], dp[j] + g[i - 1].p);
            }
        }

        ans = max(ans, dp[i]);
    }

    cout << ans;
    return 0;
}
