#include <iostream>

using namespace std;
const int N = 100000;
const int M = 18; // log2(N) => log2(100000) ~ 17

int lg[N + 1];
int sp[N + 1][M + 1];
int a[N + 1];

int get(int l, int r) {
    int len = r - l + 1;
    int pw = lg[len];

    return min(sp[l][pw], sp[r - (1 << pw) + 1][pw]);
}

int main() {
    for (int i = 2; i <= N; ++i) {
        lg[i] = lg[i / 2] + 1;
    }
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sp[i][0] = a[i];
    }

    for (int i = 1; (1 << i) <= n; ++i) {
        int len = (1 << i);
        for (int j = 1; j + len - 1 <= n; j++) {
            int tail = j + len - 1;
            sp[j][i] = min(sp[j][i - 1], sp[tail - len / 2 + 1][i - 1]);
        }
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int l;
        int r;
        cin >> l >> r;
        cout << get(l, r) << " ";
    }
}
