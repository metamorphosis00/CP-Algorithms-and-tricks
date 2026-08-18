#include <iostream>
#include <string>
#include <random>
#include <chrono>
using namespace std;

/*
  Simple interactor example (guess the number style).

  Protocol:
  - Interactor generates a secret number.
  - Solution asks questions of the form "? x"
  - Interactor answers "<", ">" or "="
  - Solution finishes with "! x"
  - Interactor checks the final answer and exits 0/1.

  Important: always flush after every output (endl or cout.flush()).
  Solution must also flush.
*/

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char* argv[]) {
    if (argc > 1) rng.seed(stoull(argv[1]));

    // Secret number in [1, 100]
    int secret = uniform_int_distribution<int>(1, 100)(rng);
    int queries = 0;
    const int MAX_QUERIES = 20;

    while (true) {
        string type;
        if (!(cin >> type)) {
            cerr << "Solution terminated without answer\n";
            return 1;
        }

        if (type == "?") {
            int x;
            cin >> x;
            queries++;
            if (queries > MAX_QUERIES) {
                cerr << "Too many queries\n";
                return 1;
            }
            if (x < secret) cout << ">\n" << flush;
            else if (x > secret) cout << "<\n" << flush;
            else cout << "=\n" << flush;
        } else if (type == "!") {
            int x;
            cin >> x;
            if (x == secret) {
                // Correct
                return 0;
            } else {
                cerr << "Wrong answer: expected " << secret << ", got " << x << "\n";
                return 1;
            }
        } else {
            cerr << "Unknown command: " << type << "\n";
            return 1;
        }
    }
}
