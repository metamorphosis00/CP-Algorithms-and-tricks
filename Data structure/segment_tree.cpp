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
int t[4 * N + 1], a[N + 1];
void build(int v, int tl, int tr)
{
    if (tl == tr) {
        t[v] = a[tl];
        return;
    }
    int tm = (tl + tr) >> 1;
    build(2 * v, tl, tm);
    build(2 * v + 1, tm + 1, tr);
    t[v] = t[2 * v] + t[2 * v + 1];
}
void upd(int v, int tl, int tr, int id, int x)
{
    if (tl == tr) {
        t[v] = x;
        return;
    }
    int tm = (tl + tr) >> 1;
    if (id <= tm) {
        upd(2 * v, tl, tm, id, x);
    }
    else {
        upd(2 * v + 1, tm + 1, tr, id, x);
    }
    t[v] = t[2 * v] + t[2 * v + 1];
}
int getSum(int v, int tl, int tr, int L, int R)
{
    if (tl == L && tr == R) {
        return t[v];
    }
    int tm = (tl + tr) >> 1;
    if (R <= tm) {
        return getSum(2 * v, tl, tm, L, R);
    }
    else if (L > tm) {
        return getSum(2 * v + 1, tm + 1, tr, L, R);
    }
    return getSum(2 * v, tl, tm, L, tm) + getSum(2 * v + 1, tm + 1, tr, tm + 1, R);
}
main()
{
    int n = readInt(), m = readInt();
    for (int i = 1; i <= n; i++) {
        a[i] = readInt();
    }
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int type = readInt();
        if (type == 1) {
            int l = readInt(), r = readInt();
            printf("%I64d\n", getSum(1, 1, n, l, r));
        }
        else {
            int id = readInt(), x = readInt();
            upd(1, 1, n, id, x);
        }
    }
}
