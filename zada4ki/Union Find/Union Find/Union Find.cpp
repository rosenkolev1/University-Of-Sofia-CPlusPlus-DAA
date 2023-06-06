// Union Find.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

std::vector<int> parent = std::vector<int>();
std::vector<int> height = std::vector<int>();

int n, m;

int root(int node) {

    int u = node;
    while (u != parent[u]) {
        u = parent[u];
    }

    parent[node] = u;

    return u;
}

void join(int u, int v) {
    if (height[u] > height[v]) {
        parent[v] = u;
    }
    else {
        parent[u] = v;

        if (height[u] == height[v]) {
            height[v]++;
        }
    }
}

int main()
{

    for (int i = 0; i < 100001; i++) {
        parent.push_back(i);
        height.push_back(0);
    }

    scanf("%d %d", &n, &m);

    if (n == 1) {
        printf("0");
        return 0;
    }

    for (int i = 0; i < m; i++) {
        int a, b;

        scanf("%d %d", &a, &b);

        int rootA = root(a);
        int rootB = root(b);

        if (rootA != rootB) {
            join(rootA, rootB);

            --n;
            \
            if (n == 1) {
                printf("%d", i + 1);
                return 0;
            }
        }
    }

    printf("-1");
}
