/**
implementation kuhn's optimized algorithm
for find maximum matching in given bipartite graph
on example Codeforces problem BerSU Ball https://codeforces.com/contest/489/problem/B
**/
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5;

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
vector<int> g[N + 1];
bool used[N + 1];
int mt[N + 1], ans[N + 1], _tm[N + 1];
int n1, n2;
bool try_kuhn(int v)
{
    if (used[v]) return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1) {
            mt[to] = v;
            _tm[v] = to;
            return true;
        }
    }
    for (int to : g[v]) {
        if (try_kuhn(mt[to])) {
            _tm[v] = to;
            mt[to] = v;
            return true;
        }
    }
    return false;
}
main() {
    /// read graph...
    fill(mt + 1, mt + n2 + 1, -1);
    fill(_tm + 1, _tm + n1 + 1, -1);
    int run = 1;
    while (run) {
        run = 0;
        fill(used + 1, used + n1 + 1, false);
        for (int i = 1; i <= n1; i++) {
            if (_tm[i] == -1 && try_kuhn(i)) {
                run = 1;
            }
        }
    }
    int maximum_matching = 0;
    for (int i = 1; i <= n1; i++) {
        if (_tm[i] != -1) {
            // cout << i << " " << _tm[i] << "\n";
            maximum_matching++;
        }
    }
    cout << maximum_matching;
}
