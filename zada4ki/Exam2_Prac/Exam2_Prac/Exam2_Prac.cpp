// Exam2_Prac.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cstring>

typedef long long mlong;
typedef std::pair<mlong, mlong> mlPair;

void loudAndRich_DFS(int root, int cur, std::vector<std::vector<int>>& adjList, std::vector<int>& quiet, std::vector<int>& answers, 
    std::vector<bool>& visited) {
    for (int child : adjList[cur]) {
        if (!visited[child] && quiet[answers[child]] > quiet[answers[root]]) {
            answers[child] = answers[root];
            loudAndRich_DFS(root, child, adjList, quiet, answers, visited);
            visited[child] = true;
        }

        /*if (quiet[answers[child]] > quiet[answers[root]]) {
            answers[child] = answers[root];
            loudAndRich_DFS(root, child, adjList, quiet, answers, visited);
        }

        if (!visited[child]) {
            visited[child] = true;
            loudAndRich_DFS(child, adjList, quiet, answers, visited);
        }
        else {
            int debug = 10;
        }*/
    }
}

std::vector<int> loudAndRich(std::vector<std::vector<int>>& richer, std::vector<int>& quiet) {
    int n = quiet.size();

    std::vector<std::vector<int>> adjList(n);
    //std::vector<bool> visited(n, false);

    for (auto& edge : richer) {
        adjList[edge[0]].push_back(edge[1]);
        //visited[edge[1]] = true;
    }

    //std::vector<int> startNodes = std::vector<int>();
    std::vector<int> answers = std::vector<int>();

    for (int i = 0; i < n; i++) {
        /*if (!visited[i]) {
            startNodes.push_back(i);
        }*/

        answers.push_back(i);
    }

    for (int i = 0; i < n; i++) {
        std::vector<bool> curVisited(n, false);
        curVisited[i] = true;
        loudAndRich_DFS(i, i, adjList, quiet, answers, curVisited);
    }

    return answers;
}

void allAncestors_Dfs(int root, int current, std::vector<int> adjList[1000], std::vector<std::vector<int>>&  answers, std::vector<bool>& visited) {
    visited[current] = true;

    for (int child : adjList[current]) {
        if (!visited[child]) {
            answers[child].push_back(root);
            allAncestors_Dfs(root, child, adjList, answers, visited);
        }
    }
}

std::vector<std::vector<int>> allAncestors(int n, std::vector<std::vector<int>>& edges) {

    std::vector<int> adjList[1000];
    //std::vector<bool> visited(n, false);
    std::vector<std::vector<int>> answers(n);

    for (int i = 0; i < edges.size(); i++) {
        auto& curEdge = edges[i];
        int from = curEdge[0];
        int to = curEdge[1];

        adjList[from].push_back(to);
    }
    
    for (int i = 0; i < n; i++) {
        std::vector<bool> visited(n, false);
        allAncestors_Dfs(i, i, adjList, answers, visited);
    }

    return answers;
}

bool courseSchedule(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    std::vector<std::vector<int>> adjList(numCourses);
    std::vector<std::vector<int>> revAdjList(numCourses);
    std::vector<bool> visited(numCourses, false);

    for (int i = 0; i < prerequisites.size(); i++) {
        int from = prerequisites[i][1];
        int to = prerequisites[i][0];

        adjList[from].push_back(to);
        revAdjList[to].push_back(from);

        visited[to] = true;
    }

    std::queue<int> children = std::queue<int>();

    int countOfVisited = 0;

    for (int i = 0; i < numCourses; i++) {
        if (!visited[i]) {
            children.push(i);
            visited[i] = true;
            countOfVisited++;
        }
        else {
            visited[i] = false;
        }
    }

    while (!children.empty()) {
        int cur = children.front();

        for (int child : adjList[cur]) {
            //Check if requirements are met
            bool reqMet = true;

            for (int i = 0; i < revAdjList[child].size(); i++) {
                int req = revAdjList[child][i];
                if (!visited[req]) {
                    reqMet = false;
                    break;
                }
            }

            if (!visited[child] && reqMet) {
                visited[child] = true;
                children.push(child);
                countOfVisited++;
            }
        }

        children.pop();
    }

    return countOfVisited == numCourses;
}

std::vector<int> courseSchedule_2(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    std::vector<std::vector<int>> adjList(numCourses);
    std::vector<std::vector<int>> revAdjList(numCourses);
    std::vector<bool> visited(numCourses, false);

    for (int i = 0; i < prerequisites.size(); i++) {
        int from = prerequisites[i][1];
        int to = prerequisites[i][0];

        adjList[from].push_back(to);
        revAdjList[to].push_back(from);

        visited[to] = true;
    }

    std::queue<int> children = std::queue<int>();
    //std::queue<std::vector<int>> allParents = std::queue<std::vector<int>>();

    int countOfVisited = 0;

    std::vector<int> order = std::vector<int>();

    for (int i = 0; i < numCourses; i++) {
        if (!visited[i]) {
            children.push(i);
            visited[i] = true;

            /*parents = std::vector<int>

            allParents.push();*/
            countOfVisited++;
            //order.push_back(i);
        }
        else {
            visited[i] = false;
        }
    }

    while (!children.empty()) {
        int cur = children.front();
        order.push_back(cur);

        for (int child : adjList[cur]) {
            //Check if requirements are met
            bool reqMet = true;

            for (int i = 0; i < revAdjList[child].size(); i++) {
                int req = revAdjList[child][i];
                if (!visited[req]) {
                    reqMet = false;
                    break;
                }
            }

            if (!visited[child] && reqMet) {
                visited[child] = true;
                children.push(child);
                countOfVisited++;
            }
        }

        children.pop();
    }

    if (countOfVisited != numCourses) {
        return std::vector<int>();
    }
    return order;
}

struct Edge {
    mlong from, to, sec, green, red;

    Edge(mlong from, mlong to, mlong sec, mlong green, mlong red) {
        this->from = from;
        this->to = to;
        this->sec = sec;
        this->green = green;
        this->red = red;
    }
};

void lights() {
    mlong n, m, startSecond;
    scanf("%lld %lld %lld", &n, &m, &startSecond);

    std::vector<std::vector<Edge>> adjList(n);

    for (mlong i = 0; i < m; i++) {
        mlong from, to, sec, green, red;

        scanf("%lld %lld %lld %lld %lld", &from, &to, &sec, &green, &red);

        Edge edgeFrom(from - 1, to - 1, sec, green, red);
        Edge edgeTo(to - 1, from - 1, sec, green, red);

        adjList[from - 1].push_back(edgeFrom);
        adjList[to - 1].push_back(edgeTo);
    }

    std::priority_queue<mlPair, std::vector<mlPair>, std::greater<mlPair> > heap = 
        std::priority_queue<mlPair, std::vector<mlPair>, std::greater<mlPair> >();

    heap.push(mlPair(startSecond, 0));

    std::vector<bool> visited(n, false);
    std::vector<mlong> fastestPaths(n, -1);
    fastestPaths[0] = 0;
    
    while (!heap.empty()) {
        mlPair cur = heap.top();
        heap.pop();
        mlong node = cur.second;
        mlong time = cur.first;

        if (visited[node]) {
            continue;
        }

        visited[node] = true;

        for (Edge& childEdge : adjList[node]) {
            if (visited[childEdge.to]) continue;

            mlong cycleSecond = time % (childEdge.green + childEdge.red);

            bool isGreen = cycleSecond < childEdge.green;
            mlong timePenalty = isGreen ? 0 : childEdge.green + childEdge.red - cycleSecond;

            mlong timeToCross = childEdge.sec + timePenalty;
            mlong timeAfterCross = time + timeToCross;

            if (fastestPaths[childEdge.to] == -1 || fastestPaths[childEdge.to] >= timeAfterCross) {
                fastestPaths[childEdge.to] = timeAfterCross;
            }

            heap.push(mlPair(timeAfterCross, childEdge.to));
        }
    }

    for (mlong i = 1; i < fastestPaths.size(); i++) {
        printf("%lld ", fastestPaths[i]);
    }
}

bool foundWord(mlong x, mlong y, mlong nextSymbolInd, std::string word, std::vector<std::vector<char>>& table) {
    if (nextSymbolInd >= word.size()) return true;

    mlong rows = table.size();
    mlong cols = table[0].size();

    mlPair offsets[4]{ mlPair(-1, 0), mlPair(1, 0), mlPair(0, -1), mlPair(0, 1), };

    for (auto& offset : offsets) {
        mlong newX = x - offset.first;
        mlong newY = y - offset.second;

        if (newX < 0 || newX >= rows || newY < 0 || newY >= cols) continue;

        if (table[newX][newY] == word[nextSymbolInd] && foundWord(newX, newY, nextSymbolInd + 1, word, table)) {
            return true;
        }
    }

    return false;
}

void hidden() {

    mlong n, m;

    scanf("%lld %lld", &n, &m);

    std::vector<std::vector<char>> table(n);

    std::vector<mlPair> letters[26];

    for (mlong i = 0; i < n; i++) {
        char row[51];

        scanf("%s", &row);

        std::string rowString(row);

        int curY = 0;

        for (char symbol : rowString) {
            table[i].push_back(symbol);

            letters[symbol - 'a'].push_back(mlPair(i, curY));

            curY++;
        }      
    }

    mlong k;
    scanf("%lld", &k);

    std::vector<bool> found = std::vector<bool>();

    for (mlong i = 0; i < k; i++) {
        char wordChar[51];

        scanf("%s", &wordChar);

        std::string word(wordChar);
        
        bool wordFound = false;

        for (mlPair coords : letters[word[0] - 'a']) {
            if (foundWord(coords.first, coords.second, 1, word, table)) {
                wordFound = true;
                break;
            }
        }

        found.push_back(wordFound);
    }

    for (bool wordFound : found) {
        if (wordFound) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
}

int main()
{
    //-------------------ZADA4A 6
    /*
5 6
glmnta
csoikf
dgotzf
hcnats
oemcpw
7
nato
god
meh
cat
catod
gg
stanchoemnogogotin
    */

    hidden();
}

