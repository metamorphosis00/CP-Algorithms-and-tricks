#include <iostream>

using namespace std;
const int N = 100000;
const int M = 18; // log2(N) => log2(100000) ~ 17

struct sparseTable {
    int *lg = new int[N + 1]; // use dynamic array to avoid runtime error because compiler memory limit
    int **sp = new int *[N + 1];

    sparseTable(int n) {
        lg[1] = 0;
        for (int i = 2; i <= n; ++i) {
            lg[i] = lg[i / 2] + 1;
        }

        for (int i = 1; i <= n; ++i) {
            sp[i] = new int[M + 1];
        }
    }

    void build(int n, const int a[]) {

        for (int i = 1; i <= n; ++i) {
            sp[i][0] = a[i];
        }

        for (int i = 1; (1 << i) <= n; ++i) {
            int len = (1 << i);
            for (int j = 1; j + len - 1 <= n; j++) {
                int tail = j + len - 1;
                sp[j][i] = min(sp[j][i - 1], sp[tail - len / 2 + 1][i - 1]);
            }
        }
    }

    int get(int l, int r) {
        int len = r - l + 1;
        int pw = lg[len];

        return min(sp[l][pw], sp[r - (1 << pw) + 1][pw]);
    }
};

int a[N + 1];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sparseTable table(n);
    table.build(n, a);

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int l;
        int r;
        cin >> l >> r;
        cout << table.get(l, r) << " ";
    }
}
