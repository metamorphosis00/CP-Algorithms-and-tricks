#include <iostream>
#include <vector>

using namespace std;
const int N = 100000;
const int M = 18; // log2(N) => log2(100000) ~ 17

struct sparseTable {
    vector<int> lg;
    vector<vector<int> > sp; // for find min value in segment
    vector<vector<int> > tp; // for find max value in segment

    sparseTable(int n)
    {
        lg.resize(n + 1);
        sp.resize(n + 1);
        tp.resize(n + 1);

        lg[1] = 0;
        for (int i = 2; i <= n; ++i) {
            lg[i] = lg[i / 2] + 1;
        }

        int m = lg[n] + 1;

        for (int i = 1; i <= n; ++i) {
            sp[i].resize(m + 1);
            tp[i].resize(m + 1);
        }
    }

    void build(int n, const int a[])
    {

        for (int i = 1; i <= n; ++i) {
            sp[i][0] = a[i];
            tp[i][0] = a[i];
        }

        for (int i = 1; (1 << i) <= n; ++i) {
            int len = (1 << i);
            for (int j = 1; j + len - 1 <= n; j++) {
                int tail = j + len - 1;
                sp[j][i] = min(sp[j][i - 1], sp[tail - len / 2 + 1][i - 1]);
                tp[j][i] = max(tp[j][i - 1], tp[tail - len / 2 + 1][i - 1]);
            }
        }
    }

    int getMin(int l, int r)
    {
        int len = r - l + 1;
        int pw = lg[len];

        return min(sp[l][pw], sp[r - (1 << pw) + 1][pw]);
    }

    int getMax(int l, int r)
    {
        int len = r - l + 1;
        int pw = lg[len];

        return max(tp[l][pw], tp[r - (1 << pw) + 1][pw]);
    }
};

int a[N + 1];

int main()
{
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
        cout << table.getMin(l, r) << " " << table.getMax(l, r) << endl;
    }
}
