// ShortestPathAlg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>

typedef std::pair<int, int> intPair;
typedef std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> prQueue;


void lovers() {

    int n, m;

    scanf("%d %d", &n, &m);

    std::vector<int> waitTimes = std::vector<int>();
    std::vector<std::pair<int, bool>> shortestPaths = std::vector<std::pair<int, bool>>();
    std::vector<int> fathers = std::vector<int>();

    std::unordered_map<int, std::vector<intPair>> graph = std::unordered_map<int, std::vector<intPair>>();

    for (int i = 0; i < n; i++) {
        int waitTime;

        scanf("%d", &waitTime);

        waitTimes.push_back(waitTime);
        shortestPaths.push_back(std::pair<int, bool>(-1, false));
        fathers.push_back(-1);
    }

    for (int i = 0; i < m; i++) {
        int from, to, dist;

        scanf("%d %d %d", &from, &to, &dist);

        if (graph.find(from) == graph.end()) {
            graph[from] = std::vector<intPair>();
        }

        graph[from].push_back(intPair(to, dist));
    }

    prQueue heap = prQueue();
    heap.push(intPair(0, 1));
    shortestPaths[0].first = 0;

    while (!heap.empty()) {
        auto curPair = heap.top();
        int time = curPair.first;
        int vertex = curPair.second;

        heap.pop();

        if (vertex == n) {
            printf("%d\n", time);

            //Print all the descendants

            std::vector<int> nodes = std::vector<int>();
            int curVertexInd = vertex - 1;

            while (curVertexInd != -1) {
                nodes.push_back(curVertexInd + 1);
                curVertexInd = fathers[curVertexInd];
            }

            printf("%llu\n", nodes.size());

            for (int i = nodes.size() - 1; i >= 0; i--) {
                printf("%d ", nodes[i]);
            }

            return;
        }

        int waitTime = (waitTimes[vertex - 1] - time % waitTimes[vertex - 1]) % waitTimes[vertex - 1];

        shortestPaths[vertex - 1].second = true;

        auto& neighbours = graph[vertex];

        for (int i = 0; i < neighbours.size(); i++) {
            int newVertex = neighbours[i].first;
            int newTime = neighbours[i].second;

            if (!shortestPaths[newVertex - 1].second) {
                int curShortest = shortestPaths[newVertex - 1].first;

                int newTotalTime = newTime + time + waitTime;

                if (curShortest == -1 || newTotalTime < curShortest) {
                    shortestPaths[newVertex - 1].first = newTotalTime;
                    heap.push(intPair(newTotalTime, newVertex));
                    fathers[newVertex - 1] = vertex - 1;
                }
            }
        }
    }

    printf("%d", -1);
}



int main()
{
    //lovers();
}
