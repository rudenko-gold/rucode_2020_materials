#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;

    vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, 0));
    vector<pair<int, int>> ans;
    vector<vector<pair<int, int>>> path(a.size() + 1, vector<pair<int, int>>(b.size() + 1));

    for (int i = 1; i <= a.size(); ++i) {
        for (int j = 1; j <= b.size(); ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                path[i][j] = { i - 1, j - 1 };
            } else {
                if (dp[i - 1][j] >= dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                    path[i][j] = { i - 1, j };
                } else {
                    dp[i][j] = dp[i][j - 1];
                    path[i][j] = { i, j - 1 };
                }
            }
        }
    }

    for (int i = a.size(), j = b.size(); i > 0 || j > 0; ) {
        if (path[i][j] == pair{ i - 1, j - 1 }) {
            ans.push_back({ i, j });
        }
        pair<int, int> next = path[i][j];
        i = next.first;
        j = next.second;
    }

    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].first << " ";
    }
    cout << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].second << " ";
    }

    return 0;
}
