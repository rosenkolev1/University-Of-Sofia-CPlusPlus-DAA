// Speed(UnionFind).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

struct EdgeInfo {
    int from;
    int to;
    int speed;

    EdgeInfo(int from, int to, int speed) {
        this->from = from;
        this->to = to;
        this->speed = speed;
    }

    bool operator< (const EdgeInfo& other) {
        return this->speed < other.speed;
    }
};

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

int findUnion(int n, int m, std::vector<EdgeInfo>& sortedEdges, const EdgeInfo& start, int startInd) {
    std::vector<int> parents = std::vector<int>();
    std::vector<int> heights = std::vector<int>();

    for (int i = 0; i < n; i++) {
        parents.push_back(i);
        heights.push_back(0);
    }

    for (int i = startInd; i < sortedEdges.size(); i++) {
        EdgeInfo edgeInfo = sortedEdges[i];

        int rootFrom = root(parents, edgeInfo.from);
        int rootTo = root(parents, edgeInfo.to);

        if (rootFrom != rootTo) {
            join(parents, heights, rootFrom, rootTo);

            n--;

            if (n == 1) {
                return edgeInfo.speed;
            }
        }
    }

    return -1;
}

int main()
{
    int n, m;

    scanf("%d %d", &n, &m);

    std::vector<EdgeInfo> sortedEdges = std::vector<EdgeInfo>();

    for (int i = 0; i < m; i++) {
        int from, to, speed;

        scanf("%d %d %d", &from, &to, &speed);

        sortedEdges.push_back(EdgeInfo(from - 1, to - 1, speed));
    }

    std::sort(sortedEdges.begin(), sortedEdges.end());

    int minDiff = 1000000000;
    int totalMaxSpeed = -1;
    int totalMinSpeed = -1;

    for (int i = 0; i < m; i++) {
        EdgeInfo newStart = sortedEdges[i];

        int maxSpeed = findUnion(n, m, sortedEdges, newStart, i);

        if (maxSpeed != -1 && maxSpeed - newStart.speed < minDiff) {
            minDiff = maxSpeed - newStart.speed;
            totalMaxSpeed = maxSpeed;
            totalMinSpeed = newStart.speed;
        }
    }

    printf("%d %d", totalMinSpeed, totalMaxSpeed);
}

