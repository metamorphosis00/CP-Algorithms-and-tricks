/**
Segment tree with range add and get sum of segment
tested on https://www.spoj.com/problems/ADARAIN/
**/
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e6;

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
char readChar()
{
    char result = getchar();
    while (isspace(result)) {
        result = getchar();
    }
    return result;
}
int t[4 * N + 1], col[4 * N + 1];
int n, m;
void pull(int v, int tl, int tr)
{
    int tm = (tl + tr) >> 1;
    t[v] = t[2 * v] + (tm - tl + 1) * col[2 * v] + t[2 * v + 1] + (tr - tm) * col[2 * v + 1];
}
void push(int v)
{
    col[2 * v] += col[v];
    col[2 * v + 1] += col[v];
    col[v] = 0;
}
void add(int v, int tl, int tr, int L, int R, int x)
{
    if (tl == L && tr == R) {
        col[v] += x;
        return;
    }
    push(v);
    int tm = (tl + tr) >> 1;
    if (R <= tm) {
        add(2 * v, tl, tm, L, R, x);
    }
    else if (L > tm) {
        add(2 * v + 1, tm + 1, tr, L, R, x);
    }
    else {
        add(2 * v, tl, tm, L, tm, x);
        add(2 * v + 1, tm + 1, tr, tm + 1, R, x);
    }
    pull(v, tl, tr);
}
int getSum(int v, int tl, int tr, int L, int R)
{
    if (tl == L && tr == R) {
        return t[v] + (tr - tl + 1) * col[v];
    }
    push(v);
    int tm = (tl + tr) >> 1;
    int ans = 0;
    if (R <= tm) {
        ans = getSum(2 * v, tl, tm, L, R);
    }
    else if (L > tm) {
        ans = getSum(2 * v + 1, tm + 1, tr, L, R);
    }
    else {
        ans = getSum(2 * v, tl, tm, L, tm) + getSum(2 * v + 1, tm + 1, tr, tm + 1, R);
    }
    pull(v, tl, tr);
    return ans;
}
main() {
    int n = readInt(), m = readInt(), w = readInt();
    for (int i = 1; i <= n; i++) {
        int l = readInt(), r = readInt();
        ++l;
        ++r;
        add(1, 1, w, l, r, 1);
    }
    for (int i = 1; i <= m; i++) {
        int x = readInt();
        ++x;
        cout << getSum(1, 1, w, x, x) << "\n";
    }
}
