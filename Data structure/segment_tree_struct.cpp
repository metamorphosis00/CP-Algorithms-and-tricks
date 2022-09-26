#include <iostream>

#define int long long

using namespace std;

const int N = 100000;
const int INF = 1000000000;

int readInt() {
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

struct node {
    int sum;
    int mn;
    int mx;

    node() {
        sum = 0;
        mx = -INF;
        mn = INF;
    }
};

struct segTree {
    int nn;
    node *t = new node[4 * N + 1];

    void init(int n) {
        this->nn = n;
        for (int i = 1; i <= 4 * n; ++i) {
            t[i].sum = 0;
            t[i].mn = INF;
            t[i].mx = -INF;
        }
    }

    segTree(int n = 0) {
        init(n);
    }

    void pull(int v, int tl, int tr) {
        t[v].sum = t[2 * v].sum + t[2 * v + 1].sum;
        t[v].mn = min(t[2 * v].mn, t[2 * v + 1].mn);
        t[v].mx = max(t[2 * v].mx, t[2 * v + 1].mx);
    }

    void set(int v, int x) {
        t[v].sum = x;
        t[v].mn = x;
        t[v].mx = x;
    }

    void build(int v, int tl, int tr, int a[]) {
        if (tl == tr) {
            set(v, a[tl]);

            return;
        }
        int tm = (tl + tr) >> 1;
        build(2 * v, tl, tm, a);
        build(2 * v + 1, tm + 1, tr, a);
        pull(v, tl, tr);
    }

    void build(int a[]) {
        build(1, 1, this->nn, a);
    }

    void upd(int v, int tl, int tr, int pos, int x) {
        if (tl == tr) {
            set(v, x);

            return;
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            upd(2 * v, tl, tm, pos, x);
        } else {
            upd(2 * v + 1, tm + 1, tr, pos, x);
        }
        pull(v, tl, tr);
    }

    void upd(int pos, int x) {
        upd(1, 1, this->nn, pos, x);
    }

    node get(int v, int tl, int tr, int L, int R) {
        if (tl == L && tr == R) {
            return t[v];
        }
        int tm = (tl + tr) >> 1;
        node result;
        node left;
        node right;

        if (R <= tm) {
            result = get(2 * v, tl, tm, L, R);
        } else if (L > tm) {
            result = get(2 * v + 1, tm + 1, tr, L, R);
        } else {
            left = get(2 * v, tl, tm, L, tm);
            right = get(2 * v + 1, tm + 1, tr, tm + 1, R);
            result.sum = left.sum + right.sum;
            result.mn = min(left.mn, right.mn);
            result.mx = max(left.mx, right.mx);
        }
        return result;
    }

    node get(int L, int R) {
        return get(1, 1, this->nn, L, R);
    }

    node get(int pos) {
        return get(pos, pos);
    }
};

int a[N + 1];

main() {
    int n = readInt();
    int m = readInt();
    for (int i = 1; i <= n; ++i) {
        a[i] = readInt();
    }

    segTree tree(n);

    tree.build(a);

    node res;

    for (int i = 0; i < m; ++i) {
        int type = readInt();
        if (type == 1) {
            int l = readInt();
            int r = readInt();
            res = tree.get(l, r);

            printf("%I64d\n", res.sum);
        } else {
            int id = readInt();
            int x = readInt();

            tree.upd(id, x);
        }
    }
}
