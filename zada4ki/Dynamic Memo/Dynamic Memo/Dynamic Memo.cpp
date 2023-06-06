// Dynamic Memo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    int val, ind;

    Node(int val, int ind) {
        this->val = val;
        this->ind = ind;
    }

    bool operator< (const Node& other) {
        return this->val < other.val;
    }
};

int lengthOfLIS(std::vector<int>&& nums) {
    std::vector<Node> sortedNums = std::vector<Node>();

    for (int i = 0; i < nums.size(); i++) {
        sortedNums.push_back(Node(nums[i], i));
    }

    int max = -1;
    int cur = 0;
    int lastInd = -1;
    int lastVal = -1;

    std::sort(sortedNums.begin(), sortedNums.end());

    for (int i = 0; i < nums.size(); i++) {
        if (lastVal == sortedNums[i].val) {
            lastInd = sortedNums[i].ind > lastInd ? lastInd : sortedNums[i].ind;

            // if (lastInd > sortedNums[i].ind) {
            //     lastInd = sortedNums[i].ind;
            // }
            // else {
            //     lastInd = sortedNums[i].ind > lastInd ? lastInd : sortedNums[i].ind;
            // }

            // if (cur > max) {
            //     max = cur;
            // }
            // cur = 0;
        }
        //2, 4, 3, 5, 1, 0, 7, 6

        //0, 2, 1, 4, 3, 5
        else if (lastInd < sortedNums[i].ind) {
            cur++;
            lastInd = sortedNums[i].ind;
            lastVal = sortedNums[i].val;
        }

        // lastInd = sortedNums[i].ind;
    }

    return cur;
}

int main()
{
    lengthOfLIS(std::vector<int> { 1, 3, 6, 7, 9, 4, 10, 5, 6 });
}
