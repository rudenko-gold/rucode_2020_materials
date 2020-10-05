#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

struct Segment {
    int l, r;
};

const int MAXN = 1000001;
vector<Segment> freq[MAXN];

int main() {
    int n, w;
    cin >> n >> w;

    for (int i = 0; i < w; i++) {
        int p, q;
        cin >> p >> q;
        if (p > q) {
            swap(p, q);
        }
        freq[q].push_back({p, q});
    }

    vector<Segment> seg;
    seg.reserve(w);

    for (int i = 1; i <= n; i++) {
        for (auto& s : freq[i]) {
            seg.push_back(s);
        }
    }

    Segment last = seg[0];

    for (int i = 1; i < seg.size(); ++i) {
        auto& curr = seg[i];

        if (curr.r == last.r) {
            last.l = min(curr.l, last.l);
        } else if (curr.r > last.r) {
            if (curr.l <= last.l) {
                last = curr;
            } else if (curr.l >= last.r) {
                last = curr;
            } else {
                cout << "Unsafe";
                return 0;
            }
        }
    }

    cout << "Safe";
}
