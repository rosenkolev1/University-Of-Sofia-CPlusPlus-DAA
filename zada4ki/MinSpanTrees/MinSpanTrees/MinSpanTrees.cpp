// MinSpanTrees.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

typedef std::pair<std::vector<int>, bool> mPair;
typedef std::pair<int, int> iPair;

int minCostConnectPoints(std::vector<std::vector<int>>& points) {
    std::vector<mPair> nextPoints;

    nextPoints.push_back(mPair(points[0], false));

    for (int i = 1; i < points.size(); i++) {
        nextPoints.push_back(mPair(points[i], false));
    }

    int inclusions = points.size();
    std::vector<int> curPoint = points[0];

    std::vector<int> shortestPaths(points.size(), -1);
    shortestPaths[0] = 0;

    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> heap = 
        std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>>();

    heap.push(iPair(0, 0));

    int totalMinCost = 0;

    while (inclusions > 0) {
        iPair curPoint = heap.top();
        heap.pop();

        if (nextPoints[curPoint.second].second == true) {
            continue;
        }

        inclusions--;

        totalMinCost += curPoint.first;

        int curX = nextPoints[curPoint.second].first[0];
        int curY = nextPoints[curPoint.second].first[1];

        nextPoints[curPoint.second].second = true;

        for (int i = 1; i < nextPoints.size(); i++) {
            auto point = nextPoints[i];
            bool visited = point.second;

            if (visited) continue;

            int pointX = point.first[0];
            int pointY = point.first[1];

            int distX = curX - pointX;
            int distY = curY - pointY;

            if (distX < 0) distX *= -1;
            if (distY < 0) distY *= -1;

            int newCost = distX + distY;

            if (shortestPaths[i] == -1 || shortestPaths[i] > newCost) {
                shortestPaths[i] = newCost;
            }

            heap.push(iPair(newCost, i));
        }
    }

    return totalMinCost;
}

int main()
{
    std::vector<std::vector<int>> points = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};

    minCostConnectPoints(points);
}
