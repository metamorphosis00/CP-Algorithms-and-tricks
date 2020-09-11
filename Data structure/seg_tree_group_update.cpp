#include <iostream>
#define int long long

const int N = 1e5;

using namespace std;

int t[4 * N + 1], col[4 * N + 1];
bool marked[4 * N + 1];
void pull(int v, int tl, int tr)
{
    int tm = (tl + tr) >> 1;
    t[v] = t[2 * v] * (1 - marked[2 * v]) + col[2 * v] * (tm - tl + 1) + t[2 * v + 1] * (1 - marked[2 * v + 1]) + col[2 * v + 1] * (tr - tm);
}
void push(int v)
{
    if (marked[v]) {
        col[2 * v] = col[v];
        col[2 * v + 1] = col[v];
        col[v] = 0;

        marked[2 * v] = true;
        marked[2 * v + 1] = true;
        marked[v] = false;
    }
}
void update(int v, int tl, int tr, int L, int R, int x)
{
    if (L > R)
        return;
    if (tl == L && tr == R) {
        col[v] = x;
        marked[v] = true;
        return;
    }
    push(v);

    int tm = (tl + tr) >> 1;

    update(2 * v, tl, tm, L, min(tm, R), x);
    update(2 * v + 1, tm + 1, tr, max(tm + 1, L), R, x);

    pull(v, tl, tr);
}
int getSum(int v, int tl, int tr, int L, int R)
{
    if (L > R) {
        return 0;
    }
    if (tl == L && tr == R) {
        return t[v] * (1 - marked[v]) + col[v] * (tr - tl + 1);
    }
    push(v);

    int tm = (tl + tr) >> 1;
    int ans = 0;
    ans = getSum(2 * v, tl, tm, L, min(tm, R)) + getSum(2 * v + 1, tm + 1, tr, max(L, tm + 1), R);
    pull(v, tl, tr);
    return ans;
}
main()
{
}
