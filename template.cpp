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
void printInt(int x)
{
    if (x / 10 == 0) {
        putchar(x + 48);
        return;
    }
    printInt(x / 10);
    putchar(x % 10 + 48);
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int getRand(int l, int r)
{
    return uniform_int_distribution<int>(l, r)(rng);
}
main() {
}
