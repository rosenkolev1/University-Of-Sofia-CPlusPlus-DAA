// MergeSortExercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>

//7 2 6 4 5 1 10 9 3 8 | 0
//1 7 2 6 4 5 10 9 3 8 | 5
//1 2 7 6 4 5 10 9 3 8 | 6
//1 2 3 7 6 4 5 10 9 8 | 12
//1 2 3 4 7 6 5 10 9 8 | 14
//1 2 3 4 5 7 6 10 9 8 | 16
//1 2 3 4 5 6 7 10 9 8 | 17
//1 2 3 4 5 6 7 8 10 9 | 19
//1 2 3 4 5 6 7 8 9 10 | 20

long long moves = 0;

int* merge(int* arr1, int* arr2, int size1, int size2) {
    int ind1 = 0;
    int ind2 = 0;

    int sortedArrInd = 0;
    int* sortedArr = new int[size1 + size2];

    while (ind1 + ind2 < size1 + size2) {

        //Edge case if first arrays runs out of elements
        if (ind1 == size1) {
            int second = arr2[ind2++];
            sortedArr[sortedArrInd++] = second;
            continue;
        }

        //Edge case if second arrays runs out of elements
        if (ind2 == size2) {
            int first = arr1[ind1++];
            sortedArr[sortedArrInd++] = first;
            continue;
        }
        
        int first = arr1[ind1];
        int second = arr2[ind2];

        if (first <= second) {
            sortedArr[sortedArrInd++] = first;
            ind1++;
        }
        else {
            sortedArr[sortedArrInd++] = second;
            ind2++;

            //Add to the moves counter
            moves += size1 - ind1;
        }
    }

    return sortedArr;
}

int* mergeSort(int* arr, int beg, int end) {

    if (beg == end) {
        int* singleElementArr = new int[1];
        singleElementArr[0] = arr[beg];

        return singleElementArr;
    }

    int size1 = (end - beg) / 2 + 1;
    int size2 = (end - beg + 1) - size1;

    return merge(mergeSort(arr, beg, (beg + end) / 2), mergeSort(arr, (beg + end) / 2 + 1, end), size1, size2);
}

void seatingExercise() {
    int n;

    scanf("%d", &n);

    if (n == 1) {
        printf("%d", 0);
    }

    int* desired = new int[n];

    int indexes[100000];

    for (int i = 0; i < n; i++) {
        int desiredSeat;

        scanf("%d", &desiredSeat);

        desired[i] = desiredSeat;
        indexes[desiredSeat - 1] = i;
    }

    /*for (int i = 0; i < n; i++) {
        std::cout << desired[i] << " ";
    }*/

    //std::cout << std::endl;

    //MergeSort
    int* sortedArr = mergeSort(desired, 0, n - 1);

    /*for (int i = 0; i < n; i++) {
        std::cout << sortedArr[i] << " ";
    }

    std::cout << std::endl;*/

    //for (int i = 0; i < n - 1; i++) {
    //    if (sortedArr[i] > sortedArr[i + 1]) {
    //        int c[2];

    //        delete[] c;
    //    }
    //}

    /*delete[] sortedArr;

    printf("%d", moves);*/
    printf("%lld", moves);
}


//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    ListNode* sortedList = nullptr;

    ListNode* curNode = nullptr;

    auto sortFunc = [](ListNode* first, ListNode* second) -> bool {
        if (first == nullptr) {
            return true;
        }

        if (second == nullptr) {
            return false;
        }

        return first->val > second->val;
    };

    std::sort(lists.begin(), lists.end(), sortFunc);

    while (!lists.empty()) {
        ListNode* prevNode = curNode;

        if (lists.back() == nullptr) {
            break;
        }

        curNode = new ListNode(lists.back()->val);

        if (sortedList == nullptr) sortedList = curNode;

        if (prevNode != nullptr) {
            prevNode->next = curNode;
        }

        lists.back() = lists.back()->next;

        if (lists.back() == nullptr) {
            lists.pop_back();
            continue;
        }

        auto it = std::lower_bound(lists.begin(), lists.end(), lists.back(), sortFunc);

        lists.insert(it, lists.back());

        lists.pop_back();
    }

    return sortedList;
}

int main()
{
    /*std::vector<int> something = std::vector<int>();

    something.push_back(10);
    something.push_back(9);

    auto sortFunc = [](int& first, int& second) -> bool {
        return first > second;
    };

    std::sort(something.begin(), something.end(), sortFunc);

    std::cout << something.front();

    int a = 10;*/

    /*std::vector<ListNode*> anything = std::vector<ListNode*>();
    std::vector<ListNode*>& something = anything;

    auto sortFunc = [](ListNode*& first, ListNode*& second) -> bool {
        return first->val > second->val;
    };

    std::sort(something.begin(), something.end(), sortFunc);*/

    //seatingExercise();
    //[[1,4,5],[1,3,4],[2,6]]

    std::vector<ListNode*> something = std::vector<ListNode*>(
        {
            nullptr,
            new ListNode(1, new ListNode(4, new ListNode(5))),    
        }
    );

    auto res = mergeKLists(something);

    int debug = 10;
}
