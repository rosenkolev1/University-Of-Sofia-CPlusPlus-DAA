// TwoPointersAndBucketing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

typedef long long mlong;
typedef unsigned long long umlong;
typedef unsigned long ulong;

void stories() {

    umlong n, k;

    scanf("%llu %llu", &n, &k);

    umlong mul, add, mod;

    umlong curFun;
    //umlong lastStoryDaysTold = 1;

    scanf("%llu %llu %llu %llu", &curFun, &mul, &add, &mod);

    if (n == 1) {
        printf("%llu", curFun);
        return;
    }

    umlong totalFun = curFun;

    std::deque<std::pair<umlong, mlong>> stories = std::deque<std::pair<umlong, mlong>>();
    
    umlong newFun = curFun;

    umlong daysTold = 1;
    
    for (mlong i = 1; i < n; i++) {
        newFun = (newFun * mul + add) % mod;

        if (curFun <= newFun) {
            //stories = std::deque<std::pair<umlong, mlong>>();
            stories.clear();
            daysTold = 0;
            curFun = newFun;
        }
        else {
            if (stories.empty()) {
                stories.push_back(std::pair<umlong, mlong>(newFun, i));
            }
            else {
                while (!stories.empty() && stories.back().first <= newFun) {
                    stories.pop_back();
                }

                stories.push_back(std::pair<umlong, mlong>(newFun, i));
            }

            if (daysTold >= k) {
                daysTold = i - stories.front().second;
                curFun = stories.front().first;

                stories.pop_front();
            }      
        }

        totalFun += curFun;
        daysTold++;
    }

    printf("%llu", totalFun);
}

void kElement() {
    mlong k, n, f, a, b, m;

    scanf("%lld %lld %lld %lld %lld %lld", &k, &n, &f, &a, &b, &m);

    const int BUCKETS_COUNT = 20000;
    const int BUCKETS_DIFF = 200000;

    //Count of elements in each bucket
    long buckets[BUCKETS_COUNT] = {};

    mlong curValue = 0;

    for (mlong i = 0; i < n; i++) {
        if (i == 0) {
            curValue = f;
        }
        else {
            curValue = (curValue * a + b) % m;
        }

        mlong bucketInd = curValue / BUCKETS_DIFF;
        ++buckets[bucketInd];
    }

    mlong elementsCount = 0;
    mlong targetBucket = -1;
    mlong bucketK = k;

    // Find the bucket in which bucket the kth element is
    for (mlong i = 0; i < BUCKETS_COUNT; i++) {
        mlong newElementsCount = elementsCount + buckets[i];

        if (elementsCount < k && k <= newElementsCount) {
            targetBucket = i;
            break;
        }

        bucketK -= buckets[i];
        elementsCount = newElementsCount;
    }

    //Counting sort
    long elementsCounts[BUCKETS_DIFF] = {};

    for (mlong i = 0; i < n; i++) {
        if (i == 0) {
            curValue = f;
        }
        else {
            curValue = (curValue * a + b) % m;
        }

        mlong bucketInd = curValue / BUCKETS_DIFF;
        
        if (bucketInd == targetBucket) {
            ++elementsCounts[curValue % BUCKETS_DIFF];
        }
    }

    mlong totalCount = 0;

    for (mlong i = 0; i < BUCKETS_DIFF; i++) {
        mlong curCount = elementsCounts[i];

        if (totalCount < bucketK && bucketK <= totalCount + curCount) {
            printf("%lld", i + targetBucket * BUCKETS_DIFF);
            return;
        }

        totalCount += curCount;
    }
}

int main()
{
    //stories();
    kElement();
}
