/**
Given a tree calculate farthest distance and node
for each vertex
**/
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
int dp[N + 1]; /// farthest distance from node to its subtrees
int id[N + 1], d[N + 1];
int farthest_val[N + 1], farthest_node[N + 1];
vector<int> g[N + 1];
void dfs1(int v, int p = 0)
{
    if (g[v].size() == 1) { /// leaf
        id[v] = v;
    }
    for (int to : g[v]) {
        if (to == p) {
            continue;
        }
        d[to] = d[v] + 1;
        dfs1(to, v);
        if (dp[v] < dp[to] + 1) {
            dp[v] = dp[to] + 1;
            id[v] = id[to];
        }
    }
}
void dfs2(int v, int dp2 = 0, int id2 = 1, int p = 0)
{
    map<pair<int, int>, int> mp;
    for (int to : g[v]) {
        if (to == p) {
            continue;
        }
        mp[make_pair(dp[to] + 1, id[to])]++;
    }
    if (dp2 >= dp[v]) {
        farthest_val[v]  = dp2;
        farthest_node[v] = id2;
    } else {
        farthest_val[v]  = dp[v];
        farthest_node[v] = id[v];
    }
    for (int to : g[v]) {
        if (to == p) {
            continue;
        }
        mp[make_pair(dp[to] + 1, id[to])]--;
        if (!mp[make_pair(dp[to] + 1, id[to])]) {
            mp.erase(make_pair(dp[to] + 1, id[to]));
        }
        int new_dp2 = dp2, new_id2 = id2;
        if (!mp.empty()) {
            auto it = mp.end();
            it--;
            if (new_dp2 < (*it).first.first) {
                new_dp2 = (*it).first.first;
                new_id2 = (*it).first.second;
            }
        }
        dfs2(to, new_dp2 + 1, new_id2, v);
        mp[make_pair(dp[to] + 1, id[to])]++;
    }
}
main() {
    int n = readInt();
    for (int i = 1;  i < n; i++) {
        int u = readInt(), v = readInt();
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1);
    dfs2(1);
    for (int i = 1; i <= n; i++) {
        cout << i << " " << farthest_val[i] << " " << farthest_node[i] << "\n";
    }
}


