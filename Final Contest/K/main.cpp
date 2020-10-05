#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

const int MAXN = 1000001;
int a[MAXN];
int n;

int get_mex(int window_size, int mex) {
    unordered_map<int, int> freq;
    //set<int> not_in_window = mex_set;
    int cnt = mex;
    for (int r = 0; r < window_size; r++) {
        if (freq[a[r]] == 0 && a[r] < mex) {
            cnt--;
            //not_in_window.erase(a[r]);
        }
        freq[a[r]]++;
    }

    if (/*not_in_window.empty()*/ cnt == 0) {
        return 0;
    }

    for (int l = 1; l + window_size <= n; l++) {
        if (freq[a[l - 1]] == 1 && a[l - 1] < mex) {
            //not_in_window.insert(a[l - 1]);
            cnt++;
        }

        freq[a[l - 1]]--;
        int r = l + window_size;

        if (freq[a[r - 1]] == 0 && a[r - 1] < mex) {
            // not_in_window.erase(a[r - 1]);
            cnt--;
        }

        freq[a[r - 1]]++;

        if (/*not_in_window.empty()*/ cnt == 0) {
            return l;
        }
    }

    return -1;
}

int main() {
    cin >> n;

    unordered_map<int, int> freq;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }

    int mex = 0;
    while (true) {
        if (freq.find(mex) == freq.end()) {
            break;
        } else {
            mex++;
        }
    }

    //cout << get_mex(mex, mex, a);

    if (mex == 0) {
        cout << "1 1";
        return 0;
    }

    int l = 0;
    int cnt = mex;
    freq.clear();
    int l_ans = -1;
    int r_ans = -1;
    for (int r = 0; r < n; r++) {
        if (freq[a[r]] == 0 && a[r] < mex) {
            // not_in_window.erase(a[r - 1]);
            cnt--;
        }
        freq[a[r]]++;

        if (cnt == 0) {
            while (cnt == 0) {
                if (freq[a[l]] == 1 && a[l] < mex) {
                    //not_in_window.insert(a[l - 1]);
                    cnt++;
                }

                freq[a[l]]--;
                l++;
            }

            if (l_ans == -1) {
                l_ans = l;
                r_ans = r + 1;
            } else {
                if (r_ans - l_ans + 1 > r + 1 - l + 1) {
                    l_ans = l;
                    r_ans = r + 1;
                }
            }
        }
    }

    cout << l_ans << " " << r_ans;
}
/*
15
2 4 2 3 1 3 0 4 1 2 0 1 2 3 4
*/
// map<int, int>
// 1 2 3 4 5

