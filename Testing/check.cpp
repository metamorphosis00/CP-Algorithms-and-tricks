#include<bits/stdc++.h>

using namespace std;

/**
    Get file content without
    whitespace characters
**/
vector<string> getFileContent(string filename)
{
    ifstream cin(filename);
    vector<string> a;
    string s;
    while (cin >> s) {
        a.push_back(s);
    }
    return a;
}
/**
    Standard check to outputs are equal
**/
bool areEqual()
{
    vector<string> a = getFileContent("solution_output.txt");
    vector<string> b = getFileContent("brute_output.txt");
    return a == b;
}
void run()
{
    if (areEqual()) {
        puts("OK");
        return;
    }
    puts("BAD");
    vector<string> a = getFileContent("solution_output.txt");
    vector<string> b = getFileContent("brute_output.txt");
    if (a.size() != b.size()) {
        puts("Output elements have different sizes");
    } else {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                printf("Different elements at index %d(0-indexed)\nExpected: %s\nFound: %s\n", i, b[i].c_str(), a[i].c_str());
                break;
            }
        }
    }

    system("pause");
}
main() {
    run();
}
