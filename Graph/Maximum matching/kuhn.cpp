/**
implementation Kuhn's algorithm for find maximum matching
in given bipartite graph
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
int a[N], b[N];
vector<int> g[N];
int mt[N];
bool used[N];
bool try_kuhn(int v)
{
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}
main() {
    int n = readInt();
    for (int i = 1; i <= n; i++) {
        a[i] = readInt();
    }
    int m = readInt();
    for (int j = 1; j <= m; j++) {
        b[j] = readInt();
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (abs(a[i] - b[j]) <= 1) {
                g[i].push_back(j);
            }
        }
    }
    int maximum_matching = 0;
    fill(mt + 1, mt + m + 1, -1);
    for (int i = 1; i <= n; i++) {
        fill(used + 1, used + n + 1, false);
        if (try_kuhn(i)) {
            maximum_matching++;
        }
    }
    for (int i = 1; i <= m; i++) {
        if (mt[i] != -1) {
//            cout << i << " " << mt[i] << "\n";
        }
    }
    cout << maximum_matching;
}
