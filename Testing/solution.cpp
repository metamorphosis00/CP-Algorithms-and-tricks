#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 3e6;

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
string s;
int dp[10][10][10][10], old_dp[10];
int calc(int x, int y)
{
    int n = s.size();
    int res = 0;
    for (int i = 1; i < n; i++) {
        int p = s[i - 1] - 48;
        int c = s[i] - 48;
        if (dp[p][c][x][y] >= INT_MAX) {
            return -1;
        }
        if (dp[p][c][x][y]) {
            res += dp[p][c][x][y] - 1;
        }
    }
    return res;
}
void precalc()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int x = 0; x < 10; x++) {
                for (int y = 0; y < 10; y++) {
                    int res = INT_MAX;
                    int dd[10], old_dd[10];
                    fill(dd, dd + 10, INT_MAX);
                    fill(old_dd, old_dd + 10, INT_MAX);
                    dd[i] = 0;
                    int lim = 100;
                    while (lim--) {
                        for (int f = 0; f < 10; f++) {
                            old_dd[f] = dd[f];
                            dd[f] = INT_MAX;
                        }
                        for (int f = 0; f < 10; f++) {
//                            cout << f + x << " " << f + y << " " << old_dd[f] << "\n";
                            dd[(f + x) % 10] = min(dd[(f + x) % 10], old_dd[f] + 1);
                            dd[(f + y) % 10] = min(dd[(f + y) % 10], old_dd[f] + 1);
                        }
                        if (dd[j] < INT_MAX) {
                            break;
                        }
                    }
                    dp[i][j][x][y] = dd[j];
                }
            }
        }
    }
}
main() {
    precalc();
    cin >> s;
//    cout << dp[0][0][0][1];
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            cout << calc(x, y) << " ";
        }
        puts("");
    }
}
