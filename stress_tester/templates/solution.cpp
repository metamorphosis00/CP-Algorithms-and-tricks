#include <iostream>
#include <vector>
using namespace std;

/*
  Your optimized solution goes here.
  Read from stdin, write to stdout.
  For interactive problems: always flush (endl or cout.flush()).
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ========== YOUR CODE ==========
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    // Example: just print sum (replace with real solution)
    long long sum = 0;
    for (auto x : a) sum += x;
    cout << sum << "\n";

    return 0;
}
