#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    bool up = 1;
    int cnt = 1;

    for (int i = 1; i < n; i++) {
        if (v[i] < v[i - 1] && up) {
            up ^= 1;
            cnt++;
        } else if (v[i] > v[i - 1] && !up) {
            up ^= 1;
            cnt++;
        }
    }
    
    int ans = n - cnt;
    up = 0;

    for (int i = 1; i < n; i++) {
        if (v[i] < v[i - 1] && up) {
            up ^= 1;
            cnt++;
        } else if (v[i] > v[i - 1] && !up) {
            up ^= 1;
            cnt++;
        }

    }

    cout << min(ans, n - cnt);

    return 0;
}
