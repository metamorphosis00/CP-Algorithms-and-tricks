#include <iostream>
#include <string>
using namespace std;

/*
  Optional validator.
  Reads the generated test from stdin.
  Exit 0 if the test is valid according to problem constraints,
  non-zero otherwise (test will be skipped).
*/

int main() {
    // Example constraints: 1 <= n <= 10, 1 <= a_i <= 100
    int n;
    if (!(cin >> n)) return 1;
    if (n < 1 || n > 10) {
        cerr << "n out of range\n";
        return 1;
    }
    for (int i = 0; i < n; i++) {
        long long x;
        if (!(cin >> x)) return 1;
        if (x < 1 || x > 100) {
            cerr << "a_i out of range\n";
            return 1;
        }
    }
    // No extra input
    string extra;
    if (cin >> extra) return 1;
    return 0;
}
