// graphss.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<pair<int, int>> holes = vector<pair<int, int>>();
vector<pair<int, int>> knightMoves = vector<pair<int, int>>{
    pair<int, int>(-1, -2),
    pair<int, int>(1, -2),
    pair<int, int>(2, -1),
    pair<int, int>(2, 1),
    pair<int, int>(1, 2),
    pair<int, int>(-1, 2),
    pair<int, int>(-2, 1),
    pair<int, int>(-2, -1),
};
vector<pair<int, int>> knights = vector<pair<int, int>>();

vector<vector<int>> board = vector<vector<int>>();

void knightsDfs(int boardLen, int startX, int startY) {

    queue<pair<int, int>> toVisit = queue<pair<int, int>>();
    //unordered_set<pair<int, int>> visited = unordered_set<pair<int, int>>();

    toVisit.push(pair<int, int>(startX, startY));
    //visited.insert(pair<int, int>(startX, startY));

    int moves = 0;

    int maxMoves = 0;

    int changeMove = 1;

    int horsesCount = count(knights.begin(), knights.end(), pair<int, int>(startX, startY));

    while (!toVisit.empty()) {
        auto cur = toVisit.front();

        for (int i = 0; i < knightMoves.size(); i++) {
            auto moveOffset = knightMoves[i];

            int newX = cur.first + moveOffset.first;
            int newY = cur.second + moveOffset.second;

            pair<int, int> newMove = pair<int, int>(newX, newY);

            if (newX >= 0 && newX < boardLen && newY >= 0 && newY < boardLen) {
                
                if (board[newX][newY] == 0 || board[newX][newY] > 1) {
                    int countOfKnights = board[newX][newY] - 1;//count(knights.begin(), knights.end(), newMove);

                    if (countOfKnights > 0) {
                        horsesCount += countOfKnights;
                        maxMoves = moves + 1;
                    }

                    //if (countOfKnights == knights.size()) break;

                    toVisit.push(newMove);
                    board[newX][newY] = 1;
                    //visited.insert(newMove);
                }
            }
        }

        toVisit.pop();

        changeMove--;

        if (changeMove == 0) {
            moves++;
            changeMove = toVisit.size();
        }
    }

    printf("%d %d", horsesCount, maxMoves);
}

void knightsEx() {
    int n, m, k;

    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        board.push_back(vector<int>());

        for (int y = 0; y < n; y++) {
            board[i].push_back(0);
        }
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        //holes.push_back(pair<int, int>(x, y));
        board[x][y] = -1;
    }

    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        //knights.push_back(pair<int, int>(x, y));
        if (board[x][y] == 0) board[x][y] = 2;
        else board[x][y]++;
    }

    int goalX, goalY;
    scanf("%d %d", &goalX, &goalY);

    knightsDfs(n, goalX, goalY);
}

int main()
{
    //school();
    knightsEx();
}
