// Homework 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <set>
#include <stack>

typedef long long mlong;
typedef std::pair<bool, bool> bPair;
typedef std::pair<mlong, mlong> mPair;
typedef std::pair<mlong, char> command;
//typedef std::pair<bool, mlong> cmd;

struct NodeInfo {
    mlong distance;
    mlong node;
    bool nextHigher;

    NodeInfo(mlong distance, mlong node, bool nextHigher) {
        this->distance = distance;
        this->node = node;
        this->nextHigher = nextHigher;
    }

    bool operator< (const NodeInfo& other) const {
        return this->distance > other.distance;
    }
};

void zigzag() {

    mlong n, m;

    scanf("%lld %lld", &n, &m);

    std::vector<std::vector<mPair>> adjList(n);

    for (mlong i = 0; i < m; i++) {
        mlong dist, from, to;

        scanf("%lld %lld %lld", &from, &to, &dist);

        from--;
        to--;

        adjList[from].push_back(mPair(to, dist));
        adjList[to].push_back(mPair(from, dist));
    }

    //Dijkstra with added stuff
    std::vector<bPair> visited(n, bPair(false, false)); //First boolean for nextHigher == false, Second boolean for nextHigher == true;
    std::vector<mPair> shortestPaths(n, mPair(-1, -1)); //First boolean for nextHigher == false, Second boolean for nextHigher == true;
    std::priority_queue<NodeInfo> heap = std::priority_queue<NodeInfo>();

    shortestPaths[0].second = 0;

    heap.push(NodeInfo(0, 0, true));

    while (!heap.empty()) {
        NodeInfo cur = heap.top();
        heap.pop();

        if ((!cur.nextHigher && visited[cur.node].first) ||
            (cur.nextHigher && visited[cur.node].second)) {
            continue;
        }

        if (!cur.nextHigher) visited[cur.node].first = true;
        else visited[cur.node].second = true;

        if (cur.node == n - 1) break;

        for (auto& edge : adjList[cur.node]) {
            mlong newDist = cur.distance + edge.second;

            //If it is not higher or lower, do not do anything
            if ((!cur.nextHigher && edge.first > cur.node) ||
                (cur.nextHigher && edge.first < cur.node)) {
                continue;
            }

            //If already visited, don't add or check anything
            if ((!cur.nextHigher && visited[edge.first].second) ||
                (cur.nextHigher && visited[edge.first].first)) {
                continue;
            }

            if (!cur.nextHigher) {
                if (shortestPaths[edge.first].second == -1 || shortestPaths[edge.first].second > newDist) {
                    shortestPaths[edge.first].second = newDist;
                }
            }
            else {
                if (shortestPaths[edge.first].first == -1 || shortestPaths[edge.first].first > newDist) {
                    shortestPaths[edge.first].first = newDist;
                }
            }

            heap.push(NodeInfo(newDist, edge.first, !cur.nextHigher));
        }
    }

    if (shortestPaths[n - 1].second == -1) {
        printf("%lld", shortestPaths[n - 1].first);
    }
}

mlong findRoot(std::vector<mlong>& parents, mlong ind) {
    mlong indCopy = ind;

    while (ind != parents[ind]) {
        ind = parents[ind];
    }

    parents[indCopy] = ind;

    return ind;
}

void joinRoots(std::vector<mlong>& parents, std::vector<mlong>& heights, mlong rootA, mlong rootB, mlong middleInd) {

    if (heights[rootA] > heights[rootB]) {
        parents[rootB] = rootA;
        heights[rootA] += heights[rootB];

        parents[middleInd] = rootA;
        heights[rootA]++;
    }
    else {
        parents[rootA] = rootB;
        heights[rootB] += heights[rootA];

        parents[middleInd] = rootB;
        heights[rootB]++;

        //Maybe you can optimise here by making heights[rootA] = heights[rootB];

        /*if (heights[rootA] > heights[rootB]) {
            heights[rootB]++;
        }*/
    }

}

void stringsExercise() {
    std::ios_base::sync_with_stdio(false);

    std::string str;

    std::cin >> str;

    mlong q; 

    std::cin >> q;

    std::stack<command> queries = std::stack<command>();

    for (mlong i = 0; i < q; i++) {
        char cmd[2];
        mlong ind;

        std::cin >> cmd;
        std::cin >> ind;

        bool printCommand = strcmp(cmd, "1") == 0;
        char commandChar = strcmp(cmd, "1") == 0 ? '\0' : str[ind];

        queries.push(command(ind, commandChar));

        if (!printCommand) str[ind] = '#';
    }

    std::vector<mlong> parents(str.size(), -1);
    std::vector<mlong> heights(str.size(), 0);

    char curChar = '\0';
    mlong curStart = -1;

    for (mlong i = 0; i < str.size(); i++) {
        if (str[i] != curChar) {
            curStart = i;
            curChar = str[i];
        }

        if (curChar != '#') {
            parents[i] = curStart;
            heights[curStart]++;
        }
    }

    std::stack<mlong> res = std::stack<mlong>();

    while (!queries.empty()) {
        command cmd = queries.top();
        queries.pop();

        mlong ind = cmd.first;
        char letter = cmd.second;

        //This command creates puts a # on the index normally. Now we reverse it.
        if (letter != '\0') {
            mlong leftInd = ind - 1;
            mlong rightInd = ind + 1;

            bool leftIsSame = leftInd >= 0 && str[leftInd] == letter;
            bool rightIsSame = rightInd < str.size() && str[rightInd] == letter;

            if (leftIsSame && rightIsSame) {
                mlong rootLeft = findRoot(parents, leftInd);
                mlong rootRight = findRoot(parents, rightInd);

                joinRoots(parents, heights, rootLeft, rootRight, ind); 
            }
            else if (leftIsSame) {
                mlong leftRoot = findRoot(parents, leftInd);

                parents[ind] = leftRoot;
                heights[leftRoot]++;
            }
            else if (rightIsSame) {
                mlong rightRoot = findRoot(parents, rightInd);

                parents[ind] = rightRoot;
                heights[rightRoot]++;
            }
            else {
                parents[ind] = ind;
                heights[ind] = 1;
            }

            //Restore the letter
            str[ind] = letter;
        }
        //This command prints the largest substring
        else {
            mlong root = findRoot(parents, ind);

            res.push(heights[root]);
        }
    }

    //Finally print the results;
    while (!res.empty()) {
        std::cout << res.top() << "\n";
        res.pop();
    }

    /*
AABBBBBBBBB
15
2 4
2 8
1 6
2 5
2 7
1 6
2 6
2 1
2 0
2 9
2 10
1 2

AABB##B##BB
    */

    mlong debug = 0;
}

int main()
{
    //zigzag();
    stringsExercise();
}
