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
    getline(cin, a);
    
    // **** to * Optimization
    string new_a;
    
    for (int i = 0; i < a.size(); i++) {
        if (i > 0 && new_a.back() == '*' && a[i] == '*') {

        } else {
            new_a.push_back(a[i]);
        }
    }
    a = new_a;

    getline(cin, b);
    
    vector<vector<bool>> dp(a.size() + 1, vector<bool>(b.size() + 1, false));
    dp[0][0] = true;

    if (a[0] == '*') {
        for (int j = 0; j <= b.size(); j++) {
            dp[1][j] = true;
        }
        
        // start from i = 2 instead of i = 1
        for (int i = 2; i <= a.size(); ++i)  {
            for (int j = 1; j <= b.size(); ++j) {
                if (a[i - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (a[i - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else {
                    if (a[i - 1] == b[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1];
                    } else {
                        dp[i][j] = false;
                    }
                }
            }
        }
    } else {
        for (int i = 1; i <= a.size(); ++i)  {
            for (int j = 1; j <= b.size(); ++j) {
                if (a[i - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (a[i - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else {
                    if (a[i - 1] == b[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1];
                    } else {
                        dp[i][j] = false;
                    }
                }
            }
        }
    }

    if (dp[a.size()][b.size()]) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
