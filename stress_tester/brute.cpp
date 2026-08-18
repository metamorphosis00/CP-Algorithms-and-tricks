#include <iostream>
#include <vector>
using namespace std;

/*
  Correct but slow / simple solution.
  Must produce the right answer for the constraints used by generator
  (usually small n so that O(n^2) / O(n^3) is fine).
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ========== BRUTE FORCE CODE ==========
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    // Same example: sum
    long long sum = 0;
    for (auto x : a) sum += x;
    cout << sum << "\n";

    return 0;
}
