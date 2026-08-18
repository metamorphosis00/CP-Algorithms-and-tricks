#include <iostream>
#include <random>
#include <chrono>
#include <string>
using namespace std;

// Simple, high-quality RNG
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

long long rnd(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

int main(int argc, char* argv[]) {
    // Optional seed from command line for reproducibility
    if (argc > 1) {
        rng.seed(stoull(argv[1]));
    }

    // ========== WRITE YOUR GENERATOR HERE ==========
    // Example: single test with n and array a[1..n]

    int n = rnd(1, 10);          // small for stress vs brute
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        cout << rnd(1, 100) << " \n"[i == n - 1];
    }

    // Example multi-test:
    // int t = rnd(1, 5);
    // cout << t << "\n";
    // while (t--) { ... }

    return 0;
}
