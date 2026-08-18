#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
  Custom checker for problems with multiple correct answers
  (or when you need to verify properties instead of exact match).

  Protocol used by stress.py (check mode):
    argv[1] = path to input file
    argv[2] = path to solution output
    argv[3] = path to brute output (optional)

  Exit code:
    0  → Accepted
    !=0 → Wrong Answer (print reason to stderr)
*/

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: checker <input> <sol_output> [brute_output]\n";
        return 1;
    }

    ifstream in(argv[1]);
    ifstream sol(argv[2]);
    // ifstream brute(argv[3]); // optional

    // ========== READ INPUT ==========
    int n;
    in >> n;
    vector<long long> a(n);
    for (auto& x : a) in >> x;

    // ========== READ SOLUTION OUTPUT ==========
    long long ans;
    if (!(sol >> ans)) {
        cerr << "Cannot read answer from solution\n";
        return 1;
    }

    // ========== VERIFY ==========
    // Example: check that answer equals sum of array
    long long expected = 0;
    for (auto x : a) expected += x;

    if (ans != expected) {
        cerr << "Expected " << expected << ", got " << ans << "\n";
        return 1;
    }

    // Extra tokens?
    string extra;
    if (sol >> extra) {
        cerr << "Extra output in solution\n";
        return 1;
    }

    return 0; // Accepted
}
