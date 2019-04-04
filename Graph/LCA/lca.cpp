#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5, LOGN = 16;

int readInt ()
{
    bool minus = false;
    int result = 0;
    char ch;
    ch = getchar();
    while (true)
    {
        if (ch == '-') break;
        if (ch >= '0' && ch <= '9') break;
        ch = getchar();
    }
    if (ch == '-') minus = true;
    else result = ch-'0';
    while (true)
    {
        ch = getchar();
        if (ch < '0' || ch > '9') break;
        result = result*10 + (ch - '0');
    }
    if (minus)
        return -result;
    else
        return result;
}
int tin[N + 1], tout[N + 1], _time;
int up[N + 1][LOGN + 1];
vector<int> g[N + 1];
void dfs(int v, int p = 0) {
    up[v][0] = p;
    for (int i = 1; i <= LOGN; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    tin[v] = ++_time;
    for (int to : g[v]) {
        if (to == p) {
            continue;
        }
        dfs(to, v);
    }
    tout[v] = ++_time;
}
bool upper(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}
int lca(int a, int b) {
    if (upper(a, b))
        return a;
    if (upper(b, a))
        return b;
    for (int i = LOGN; i >= 0; i--) {
        if (!upper(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}
int getKth(int v, int k) /// get k-th parent of vertex v
{
    for (int i = LOGN; i >= 0; i--) {
        if ((1ll << i) <= k) {
            v = up[v][i];
            k -= (1ll << i);
        }
    }
    return v;
}
main() {
    int n = readInt();
    for (int i = 1; i < n; i++) {
        int u, v;
        u = readInt();
        v = readInt();
        g[u].push_back(v);
        swap(u, v);
        g[v].push_back(u);
    }
    dfs(1);
//    cout << lca(1, n) << " " << getKth(3, 4);
}
