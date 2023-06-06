// Repairs(Prim Algorithm).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>

using Pair = std::pair<int, int>;

int n, m;
std::vector<Pair> adjList[10001];
bool visited[10001];

int root(std::vector<int>& parents, int a) {
    int aCopy = a;

    while (a != parents[a]) {
        a = parents[a];
    }

    parents[aCopy] = a;

    return a;
}

void join(std::vector<int>& parents, std::vector<int>& heights, int a, int b) {
    if (heights[a] > heights[b]) {
        parents[b] = a;
    }
    else {
        parents[a] = b;

        if (heights[a] == heights[b]) {
            heights[b]++;
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);

    long long total = 0;

    for (int i = 0; i < m; i++) {
        int a, b, d;
        scanf("%d %d %d", &a, &b, &d);

        adjList[a].push_back({ b, d });
        adjList[b].push_back({ a, d });

        total += d;
    }

    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;

    pq.push({ 0, 1 });

    long long mpd = 0;

    while (!pq.empty()) {
        const auto [edgeWeight, u] = pq.top();

        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        mpd += (long long)edgeWeight;

        for (const auto [v, w] : adjList[u]) {
            if (!visited[v]) {
                pq.push({ w, v });
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            printf("-1");
            return 0;
        }
    }

    printf("%lld", total - mpd);
}