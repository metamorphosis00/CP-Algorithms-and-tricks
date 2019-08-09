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
char readChar()
{
    char result = getchar();
    while (isspace(result)) {
        result = getchar();
    }
    return result;
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int getRand(int l, int r)
{
    return uniform_int_distribution<int>(l, r)(rng);
}
main() {
    /// generate random test...
    int n = getRand(5, 20);
    cout << 0;
    --n;
    for (int i = 1; i <= n; i++) {
        cout << getRand(0, 9);
    }
    puts("");
}
