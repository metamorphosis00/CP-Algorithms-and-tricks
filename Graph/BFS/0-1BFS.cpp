/**
Problem: Given a graph where every edge has weight as either 0 or 1.
A source vertex is also given in the graph.
Find the shortest path from source vertex to every other vertex.
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
vector<pair<int, int> > g[N + 1];
int d[N + 1], n;
void init(int n)
{
    for (int i = 0; i <= n; i++) {
        g[i].clear();
        d[i] = INT_MAX;
    }
}
void zeroOneBFS(int src)
{
    deque<int> q;
    q.push_back(src);
    d[src] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (auto edge : g[v]) {
            int to = edge.first, cost = edge.second;
            if (d[to] > d[v] + cost) {
                d[to] = d[v] + cost;
                if (cost == 0) {
                    q.push_front(to);
                } else {
                    q.push_back(to);
                }
            }
        }
    }
}
void addEdge(int u, int v, int wt)
{
   g[u].push_back({v, wt});
   g[v].push_back({u, wt});
}
main() {
    n = 8;
    init(n);
    addEdge(0, 1, 0);
    addEdge(0, 7, 1);
    addEdge(1, 7, 1);
    addEdge(1, 2, 1);
    addEdge(2, 3, 0);
    addEdge(2, 5, 0);
    addEdge(2, 8, 1);
    addEdge(3, 4, 1);
    addEdge(3, 5, 1);
    addEdge(4, 5, 1);
    addEdge(5, 6, 1);
    addEdge(6, 7, 1);
    addEdge(7, 8, 1);
    int src = 0;//source node
    zeroOneBFS(src);
    for (int i = 0; i <= n; i++) {
        cout << d[i] << " ";
    }
    puts("");
}


