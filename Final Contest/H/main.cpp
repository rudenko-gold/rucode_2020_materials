#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int j = 0; j < n; ++j) {
        cin >> b[j];
    }

    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());

    int mipt_score = 0;
    int hse_score = 0;

    for (int i = 0; i < n; i++) {
        mipt_score += a[i];

        if (abs(mipt_score - hse_score) >= m) {
            if (mipt_score > hse_score) {
                cout << "MIPT";
                return 0;
            } else {
                cout << "HSE";
                return 0;
            }
        }

        hse_score += b[i];

        if (abs(mipt_score - hse_score) >= m) {
            if (mipt_score > hse_score) {
                cout << "MIPT";
                return 0;
            } else {
                cout << "HSE";
                return 0;
            }
        }
    }

    cout << "NO";

}
