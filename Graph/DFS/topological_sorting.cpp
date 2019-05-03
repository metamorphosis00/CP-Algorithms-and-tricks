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
int used[N + 1];
vector<int> g[N + 1], ans;
int n, m;
void dfs(int v)
{
    used[v] = 1;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to]) {
            dfs(to);
        }
        else if (used[to] == 1) {
            puts("Impossible");
            exit(0);
        }
    }
    used[v] = 2;
    ans.push_back(v);
}

void topological_sort()
{
    for (int i = 1; i <= n; ++i)
        used[i] = false;
    ans.clear();
    for (int i = 1; i <= n; ++i)
        if (!used[i])
            dfs(i);
    reverse(ans.begin(), ans.end());
}
main()
{
    n = readInt(), m = readInt();
    for (int i = 1; i <= m; i++) {
        int u = readInt(), v = readInt();
        g[u].push_back(v);
    }
    topological_sort();
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
}
