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
namespace number {
    vector<int> primes;
    vector<char> p;
    vector<int> lp;

    bool isPrime(int n)
    {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    bool isPerfectSquare(int n)
    {
        int sq = sqrt(n);
        return sq * sq == n;
    }

    int phi(int n)
    {
        int res = n;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                while (n % i == 0) {
                    n /= i;
                }
                res -= res / i;
            }
        }
        if (n > 1) {
            res -= res / n;
        }
        return res;
    }

    void sieveOfEratosthenes(int n)
    {
        primes.clear();
        p.resize(n + 1);
        lp.resize(n + 1);

        fill(p.begin(), p.end(), true);
        fill(lp.begin(), lp.end(), 0);

        p[0] = p[1] = false;

        for (int i = 2; i <= n; i++) {
            if (p[i]) {
                primes.push_back(i);
                lp[i] = i;
                for (int j = 2 * i; j <= n; j += i) {
                    lp[j] = i;
                    p[j] = false;
                }
            }
        }
    }
};
main() {
    cout << number::phi(15);
}
