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
int p[N + 1], sz[N + 1];
void make_set(int v)
{
    p[v] = v;
    sz[v] = 1;
}
int find_set(int v)
{
    if (p[v] == v) {
        return v;
    }
    return p[v] = find_set(p[v]);
}
void union_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (p[a] != p[b]) {
        if (sz[a] < sz[b]) {
            swap(a, b);
        }
        sz[a] += sz[b];
        p[b] = a;
    }
}
main() {
    int n = readInt();
    for (int i = 1; i <= n; i++) {
        make_set(i);
    }
    int m = readInt();
    for (int i = 1; i <= m; i++) {
        int u = readInt(), v = readInt();
        union_sets(u, v);
    }
}
