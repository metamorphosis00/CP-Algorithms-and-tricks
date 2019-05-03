/**
implementation Kuhn's optimized algorithm with struct
for find maximum matching in given bipartite graph
Codeforces problem BerSU Ball https://codeforces.com/contest/489/problem/B
**/
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5;

int readInt()
{
    bool minus = false;
    int result = 0;
    char ch;
    ch = getchar();
    while (true) {
        if (ch == '-')
            break;
        if (ch >= '0' && ch <= '9')
            break;
        ch = getchar();
    }
    if (ch == '-')
        minus = true;
    else
        result = ch - '0';
    while (true) {
        ch = getchar();
        if (ch < '0' || ch > '9')
            break;
        result = result * 10 + (ch - '0');
    }
    if (minus)
        return -result;
    else
        return result;
}
int a[N], b[N];
struct BipartiteMatcher {
    vector<vector<int> > G;
    vector<int> mt, tm, used;
    int T = 1;

    BipartiteMatcher(int n, int m)
        : G(n + 1)
        , mt(m + 1, -1)
        , tm(n + 1, -1)
        , used(n + 1, false)
    {
    }

    void addEdge(int a, int b)
    {
        G[a].push_back(b);
    }

    void reset()
    {
        T = 1;
        for (int i = 0; i < G.size(); i++) {
            G[i].clear();
        }
        fill(mt.begin(), mt.end(), -1);
        fill(tm.begin(), tm.end(), -1);
        fill(used.begin(), used.end(), false);
    }

    bool tryKuhn(int v)
    {
        if (used[v] == T)
            return false;
        used[v] = T;
        for (int to : G[v]) {
            if (mt[to] == -1) {
                mt[to] = v;
                tm[v] = to;
                return true;
            }
        }
        for (int to : G[v]) {
            if (tryKuhn(mt[to])) {
                mt[to] = v;
                tm[v] = to;
                return true;
            }
        }
        return false;
    }

    int getMaximumMatching()
    {
        int run = 1;
        while (run) {
            run = 0;
            for (int i = 0; i < (int)tm.size(); i++) {
                if (tm[i] == -1) {
                    ++T;
                    run += tryKuhn(i);
                }
            }
        }
        int result = 0;
        for (int i = 0; i < (int)tm.size(); i++) {
            if (tm[i] != -1) {
                result++;
            }
        }
        return result;
    }

    void solve()
    {
        /// your code here
        cout << getMaximumMatching() << "\n";
    }
};
main()
{
    int n = readInt();
    for (int i = 1; i <= n; i++) {
        a[i] = readInt();
    }
    int m = readInt();
    for (int j = 1; j <= m; j++) {
        b[j] = readInt();
    }
    BipartiteMatcher matcher(n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (abs(a[i] - b[j]) <= 1) {
                matcher.addEdge(i, j);
            }
        }
    }
    matcher.solve();
}
