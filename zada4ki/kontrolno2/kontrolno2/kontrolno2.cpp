// kontrolno2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

typedef long long mlong;
typedef std::pair<mlong, mlong> mPair;

//mlong officeDFS(std::vector<std::vector<char>>& arr, mlong startRow, mlong startCol, std::vector<std::vector<mlong>>& closest) {
//
//    if (arr[startRow][startCol] == '@') return 0;
//
//    std::queue<mPair> next = std::queue<mPair>();
//    std::queue<mPair> nextTemp = std::queue<mPair>();
//    std::vector<mPair> visited = std::vector<mPair>();
//
//    mlong rowCount = arr.size();
//    mlong colCount = arr[0].size();
//
//    next.push(mPair(startRow, startCol));
//    visited.push_back(mPair(startRow, startCol));
//    arr[startRow][startCol] = '^';
//
//    std::vector<mPair> offsets = std::vector<mPair>
//    {
//        mPair(-1, 0),
//        mPair(0, 1),
//        mPair(1, 0),
//        mPair(0, -1)
//    };
//
//    mlong curLevel = 0;
//
//    while (!next.empty()) {
//
//        mPair cur = next.front();
//
//        next.pop();
//
//        bool foundFood = false;
//
//        for (auto& offset : offsets) {
//            mPair newCell = mPair(cur.first + offset.first, cur.second + offset.second);
//
//            //Check if outside array boundaries
//            if (newCell.first < 0 || newCell.first >= rowCount ||
//                newCell.second < 0 || newCell.second >= colCount) {
//
//                continue;
//            }
//
//            if (arr[newCell.first][newCell.second] == '@') {
//                foundFood = true;
//                break;
//            }
//            else if (arr[newCell.first][newCell.second] == '.') {
//                nextTemp.push(newCell);
//                arr[newCell.first][newCell.second] = '^';
//                visited.push_back(newCell);
//            }
//        }
//
//        if (foundFood) {
//            break;
//        }
//
//        if (next.empty()) {
//            curLevel++;
//
//            //Transfer from nextTemp to next
//            while (!nextTemp.empty()) {
//                mPair nextCell = nextTemp.front();
//                next.push(nextCell);
//
//                nextTemp.pop();
//            }
//        }
//    }
//
//    //Restore the modified array
//    for (auto& cell : visited) {
//        arr[cell.first][cell.second] = '.';
//    }
//
//    return curLevel + 1;
//}
//
//void office() {
//    mlong n, m, k;
//
//    scanf("%lld %lld %lld", &n, &m, &k); 
//    
//    // . -> free
//    // # -> taken
//    // ^ -> visited
//    // @ -> food
//
//    std::vector<std::vector<char>> arr(n);
//
//    for (mlong i = 0; i < n; i++) {
//        char str[601];
//
//        scanf("%s", &str);
//
//        for (mlong y = 0; y < m; y++) {
//            arr[i].push_back(str[y]);
//        }
//    }
//
//    std::vector<std::vector<mlong>> closest(n, std::vector<mlong>(m, -1));
//
//    std::vector<mPair> foodCells(k);
//
//    for (mlong i = 0; i < k; i++) {
//        mlong row, col;
//
//        scanf("%lld %lld", &row, &col);
//
//        arr[row - 1][col - 1] = '@';
//
//        foodCells.push_back(mPair(row - 1, col - 1));
//    }
//
//    mlong allClosest = 0;
//
//    //DFS
//    for (auto& foodCell : foodCells) {
//        officeDFS(arr, foodCell.first, foodCell.second, closest);
//    }
//
//    for (mlong row = 0; row < n; row++) {
//        for (mlong col = 0; col < m; col++) {
//            if (closest[row][col] != -1) {
//                mlong closest = officeDFS(arr, row, col);
//
//                allClosest += closest;
//            }
//        }
//    }
//
//    printf("%lld", allClosest);
//}

//void game() {
//    mlong n, m, totalPoints;
//
//    scanf("%lld %lld %lld", &n, &m, &totalPoints);
//
//    std::vector<std::vector<mPair>> adjList(n);
//
//    for (mlong i = 0; i < m; i++) {
//        mlong points, time;
//        mlong from, to;
//
//        scanf("%lld %lld %lld %lld", &from, &to, &points, &time);
//
//        from--;
//        to--;
//
//        adjList[from].push_back(mPair(to, time - points));
//        adjList[to].push_back(mPair(from, time - points));
//    }
//
//    std::vector<bool> visited(n, false);
//    std::vector<mlong> shortestPaths(n, -1);
//    std::priority_queue<mPair, std::vector<mPair>, std::greater<mPair>> heap = 
//        std::priority_queue<mPair, std::vector<mPair>, std::greater<mPair>>();
//
//    heap.push(mPair(0, 0));
//
//    while (!heap.empty()) {
//        mPair cur = heap.top();
//        heap.pop();
//
//        if (visited[cur.second]) {
//            continue;
//        }
//
//        visited[cur.second] = true;
//
//        if (cur.second == n - 1) {
//            break;
//        }
//
//        if (shortestPaths[cur.second] == -1 || shortestPaths[cur.second] > cur.first) {
//            shortestPaths[cur.second] = cur.first;
//        }
//
//        for (auto& child : adjList[cur.second]) {
//            mlong next = child.first;
//            mlong weight = child.second;
//            mlong newMin = weight + cur.first;
//
//            if (shortestPaths[next] == -1 || shortestPaths[next] > newMin) {
//                shortestPaths[next] = newMin;
//            }
//
//            heap.push(mPair(newMin, next));
//        }
//    }
//
//    printf("%lld", totalPoints - shortestPaths[n - 1]);
//}
//
//void remont() {
//    mlong n, m;
//
//    scanf("%lld %lld", &n, &m);
//
//    std::vector<mlong> repCosts(n);
//    //std::vector<std::vector<mPair>> adjList(n);
//    std::vector<EdgeInfo> edges;
//
//    std::vector<mlong> parents;
//
//    for (mlong i = 0; i < n; i++) {
//        mlong cost;
//
//        scanf("%lld", &cost);
//
//        repCosts[i] = cost;
//
//        parents.push_back(i);
//    }
//
//    for (mlong i = 0; i < m; i++) {
//        mlong from, to, dist;
//
//        scanf("%lld %lld %lld", &from, &to, &dist);
//
//        from--;
//        to--;
//
//        mlong repCostFrom = repCosts[from];
//        mlong repCostTo = repCosts[to];
//
//        if (dist % 2 == 0) {
//            mlong totalCostFrom = repCostFrom * (dist / 2);
//            mlong totalCostTo = repCostTo * (dist / 2);
//
//            mlong totalCost = totalCostFrom + totalCostTo;
//
//            /*adjList[from].push_back(mPair(to, totalCost));
//            adjList[to].push_back(mPair(from, totalCost));*/
//
//            edges.push_back(EdgeInfo(from, to, totalCost));
//        }
//        else {
//            if (from > to) {
//                mlong totalCostFrom = repCostFrom * (dist / 2);
//                mlong totalCostTo = repCostTo * ((dist / 2) + 1);
//
//                mlong totalCost = totalCostFrom + totalCostTo;
//
//                /*adjList[from].push_back(mPair(to, totalCost));
//                adjList[to].push_back(mPair(from, totalCost));*/
//
//                edges.push_back(EdgeInfo(from, to, totalCost));
//            }
//            else {
//                mlong totalCostFrom = repCostFrom * ((dist / 2) + 1);
//                mlong totalCostTo = repCostTo * (dist / 2);
//
//                mlong totalCost = totalCostFrom + totalCostTo;
//
//                /*adjList[from].push_back(mPair(to, totalCost));
//                adjList[to].push_back(mPair(from, totalCost));*/
//
//                edges.push_back(EdgeInfo(from, to, totalCost));
//            }
//        }
//    }
//
//    //Kruskal
//    std::sort(edges.begin(), edges.end());
//
//    std::vector<mlong> heights(m, 0);
//
//    mlong inclusion = n - 1;
//
//    std::vector<EdgeInfo> repairedEdges;
//
//    mlong totalRepairCost = 0;
//
//    for (auto& edge : edges) {
//        
//        mlong rootA = findRoot(edge.from, parents);
//        mlong rootB = findRoot(edge.to, parents);
//
//        if (rootA != rootB) {
//            joinRoots(rootA, rootB, heights, parents);
//
//            totalRepairCost += edge.weight;
//
//            repairedEdges.push_back(edge);
//
//            inclusion--;
//
//            if (inclusion < 0) {
//                break;
//            }
//        }
//    }
//
//    printf("%lld\n", totalRepairCost);
//
//    std::sort(repairedEdges.begin(), repairedEdges.end(), [](const EdgeInfo& first, const EdgeInfo& second) -> bool {
//        if (first.from == second.from) {
//            return first.to < second.to;
//        }
//
//        return first.from < second.from;
//    });
//
//    for (auto& edge : repairedEdges) {
//        mlong from = edge.from > edge.to ? edge.to : edge.from;
//        mlong to = edge.from <= edge.to ? edge.to : edge.from;
//
//        printf("%lld %lld\n", from + 1, to + 1);
//    }
//}

struct EdgeInfo {
    mlong from, to, weight;

    EdgeInfo(mlong from, mlong to, mlong weight) {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }

    bool operator< (const EdgeInfo& other) {
        return this->weight < other.weight;
    }
};

//void interstellarDFS(std::pair<mlong, mPair> start, )

mlong findRoot(mlong node, std::vector<mlong>& parents) {

    mlong nodeCopy = node;

    while (node != parents[node]) {
        node = parents[node];
    }

    parents[nodeCopy] = node;

    return node;
}

void joinRoots(mlong rootA, mlong rootB, std::vector<mlong>& height, std::vector<mlong>& parents) {

    if (height[rootA] > height[rootB]) {
        parents[rootB] = rootA;
    }
    else {
        parents[rootA] = rootB;

        if (height[rootA] == height[rootB]) {
            height[rootB]++;
        }
    }
}

bool interstellarDFS(mlong start, mlong cur, mlong maxTemp, std::stack<mlong>& path,
    std::vector<std::vector<EdgeInfo>>& adjList, std::vector<bool>& curVisited, std::vector<bool>& prevVisited) {

    if (curVisited[cur]) {
        return true;
    }

    path.push(cur);
    curVisited[cur] = true;
    prevVisited[cur] = true;

    for (auto& edge : adjList[cur]) {

        if (edge.weight > maxTemp) {
            continue;
        }

        if (curVisited[edge.to]) {
            return true;
        }

        if (!prevVisited[edge.to]) {
            bool containsCycle = interstellarDFS(start, edge.to, maxTemp, path, adjList, curVisited, prevVisited);

            if (containsCycle) return true;
        }
        
    }

    curVisited[cur] = false;

    return false;
}

void interstellar() {
    mlong n, m;

    scanf("%lld %lld", &n, &m);

    std::vector<std::vector<EdgeInfo>> adjList(n);
    std::vector<EdgeInfo> edges = std::vector<EdgeInfo>();

    for (mlong i = 0; i < m; i++) {
        mlong from, to, weight;

        scanf("%lld %lld %lld", &from, &to, &weight);

        from--;
        to--;

        EdgeInfo newEdge = EdgeInfo(from, to, weight);

        adjList[from].push_back(EdgeInfo(from, to, weight));
        edges.push_back(newEdge);
    }

    std::sort(edges.begin(), edges.end());

    std::vector<mlong> nodes = std::vector<mlong>();
    std::vector<bool> includedNodes(n, false);

    //std::vector<mlong> lastCorPath = std::vector<mlong>();

    mlong maxTemp = -1;

    for (mlong i = 0; i < edges.size(); i++) {

        auto& edge = edges[i];
        //std::vector<mlong> newPath = std::vector<mlong>();

        if (!includedNodes[edge.from]) {
            nodes.push_back(edge.from);
        }

        if (!includedNodes[edge.to]) {
            nodes.push_back(edge.to);
        }

        includedNodes[edge.from] = true;
        includedNodes[edge.to] = true;

        std::vector<bool> totalVisited(n, false);

        bool foundMax = false;

        for (mlong node : nodes) {
            if (!totalVisited[node]) {
                std::stack<mlong> path = std::stack<mlong>();
                std::vector<bool> curVisited(n, false);

                bool containsCycle = interstellarDFS(node, node, edge.weight, path, adjList, curVisited, totalVisited);

                if (containsCycle) {
                    maxTemp = edges[i].weight - 1;
                    foundMax = true;
                    break;
                }

                /*while (!path.empty()) {
                    visited[path.top()] = true;
                    newPath.push_back(path.top());
                    path.pop();
                }*/
            } 
        }

        if (foundMax) {
            break;
        }
    }

    printf("%lld\n", maxTemp);

    std::vector<mlong> countOfOutwards(n, 0);
    std::vector<mlong> startingNodes = std::vector<mlong>();
    std::vector<std::vector<EdgeInfo>> revAdjList(n);

    for (auto& edge : edges) {
        if (edge.weight <= maxTemp) {
            countOfOutwards[edge.from]++;

            revAdjList[edge.to].push_back(EdgeInfo(edge.to, edge.from, edge.weight));
        } 
    }

    //DFS
    std::vector<bool> totalVisited(n, false);

    //BFS
    std::vector<bool> visited
    std::queue<mlong> next = std::queue<mlong>();

    for (mlong i = 0; i < n; i++) {
        if (countOfOutwards[i] == 0) {
            next.push(i);
        }        
    }

    while (!next.empty()) {

    }

    for (mlong i = 0; i < n; i++) {

        //if (countOfOutwards[i] == 0) {
        //    std::stack<mlong> path = std::stack<mlong>();
        //    std::vector<bool> curVisited(n, false);

        //    interstellarDFS(i, i, maxTemp, path, revAdjList, curVisited, totalVisited);

        //    std::queue<mlong> acPath = std::queue<mlong>();

        //    while (!path.empty()) {
        //        printf("%lld ", path.top() + 1);
        //        path.pop();
        //    }

        //    /*while (!acPath.empty()) {

        //        printf("%lld ", acPath.front() + 1);
        //        acPath.pop();
        //    }*/
        //}        
    }

    //mlong inclusion = n - 1;

    //bool foundCycle = false;
    //mlong maxTemp = -1;

    //for (auto& edge : edges) {

    //    mlong rootA = findRoot(edge.from, parents);
    //    mlong rootB = findRoot(edge.to, parents);

    //    if (rootA == rootB) {
    //        printf("%lld", edge.weight - 1);
    //        maxTemp = edge.weight - 1;

    //        foundCycle = true;
    //        break;
    //    }
    //    else {
    //        joinRoots(rootA, rootB, heights, parents);
    //        inclusion--;
    //    }

    //    //if (inclusion)
    //}

    //if (!foundCycle) {
    //    printf("%lld", -1);
    //}

    ////DFS za vuzmojen put
    //std::vector<bool> visited(n, false);
    //std::stack<mlong> path = std::stack<mlong>();

    //for (mlong i = 0; i < n; i++) {
    //    interstellarDFS(i, i, maxTemp, path, adjList, visited);
    //}

    //while (!path.empty()) {
    //    printf("%lld ", path.top());
    //    path.pop();
    //}
}

int main()
{
    //office();
    //interstellar();
    //game();

    //remont();

    interstellar();
}
