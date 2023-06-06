// GeneralGraphProblems.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

typedef long long mlong;

struct Edge {
    mlong from;
    mlong to;
    mlong weight;

    Edge(mlong from, mlong to, mlong weight) {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }

    bool operator< (const Edge& other) const {
        return this->weight > other.weight;
    }
};

mlong findRoot(mlong node, std::vector<mlong>& parents) {
    mlong u = node;

    while (u != parents[u]) {
        u = parents[u];
    }

    parents[node] = u;

    return u;
}

void join(mlong u, mlong v, std::vector<mlong>& parents, std::vector<mlong>& height) {
    if (height[u] > height[v]) {
        parents[v] = u;
    }
    else {
        parents[u] = v;

        if (height[u] == height[v]) {
            height[v]++;
        }
    }
}

int main()
{
    std::vector<Edge> graph = std::vector<Edge>();
    std::vector<mlong> parents = std::vector<mlong>();
    std::vector<mlong> heights = std::vector<mlong>();

    mlong res = 0;

    mlong n, m;

    scanf("%lld %lld", &n, &m);

    for (int i = 0; i < n; i++) {

        parents.push_back(i);
        heights.push_back(0);
    }

    for (mlong i = 0; i < m; i++) {
        mlong from, to, w;

        scanf("%lld %lld %lld", &from, &to, &w);

        Edge newEdge = Edge(from - 1, to - 1, w);

        graph.push_back(newEdge);
    }

    mlong boatW;

    scanf("%lld", &boatW);

    std::sort(graph.begin(), graph.end());

    for (mlong i = 0; i < m; i++) {
        auto curEdge = graph[i];

        mlong rootA = findRoot(curEdge.from, parents);
        mlong rootB = findRoot(curEdge.to, parents);

        if (curEdge.weight < boatW) {
            res++;
        }

        if (rootA != rootB) {
            join(rootA, rootB, parents, heights);
            --n;

            if (n == 1) {
                break;
            }
        }
    }

    printf("%lld\n", res);
}
