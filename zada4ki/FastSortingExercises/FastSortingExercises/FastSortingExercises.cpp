// FastSortingExercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

typedef long long mlong;
typedef unsigned long long umlong;
typedef std::pair<mlong, mlong> plong;

void evilExercise() {
    mlong n, m;

    scanf("%lld", &n);
    scanf("%lld", &m);

    std::vector<std::pair<mlong, mlong>> gaps = std::vector<std::pair<mlong, mlong>>();

    for (mlong i = 0; i < m; i++) {

        mlong start, end;

        scanf("%lld", &start);
        scanf("%lld", &end);

        gaps.push_back(std::pair<mlong, mlong>(start, end));
    }

    std::sort(gaps.begin(), gaps.end(),
        [](std::pair<mlong, mlong> first, std::pair<mlong, mlong> second) -> bool {
            return first.first < second.first;
        });

    mlong start = gaps[0].first, end = gaps[0].second, newStart, newEnd;

    mlong covered = 0;

    for (mlong i = 1; i < m; i++) {
        newStart = gaps[i].first;
        newEnd = gaps[i].second;

        if (newStart <= end && newEnd >= end) {
            end = newEnd;
        }
        else if (newStart > end) {
            mlong count = end - start + 1;

            covered += count;

            start = newStart;
            end = newEnd;
        }
    }

    covered += end - start + 1;

    printf("%lld", covered);
}

// FastSortingExercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

typedef long long mlong;
typedef std::pair<mlong, mlong> plong;

//void evilExercise() {
//    mlong n, m;
//
//    scanf("%lld", &n);
//    scanf("%lld", &m);
//
//    std::vector<std::pair<mlong, mlong>> gaps = std::vector<std::pair<mlong, mlong>>();
//
//    for (mlong i = 0; i < m; i++) {
//
//        mlong start, end;
//
//        scanf("%lld", &start);
//        scanf("%lld", &end);
//
//        gaps.push_back(std::pair<mlong, mlong>(start, end));
//    }
//
//    std::sort(gaps.begin(), gaps.end(),
//        [](std::pair<mlong, mlong> first, std::pair<mlong, mlong> second) -> bool {
//            return first.first < second.first;
//        });
//
//    mlong start = gaps[0].first, end = gaps[0].second, newStart, newEnd;
//
//    mlong covered = 0;
//
//    for (mlong i = 1; i < m; i++) {
//        newStart = gaps[i].first;
//        newEnd = gaps[i].second;
//
//        if (newStart <= end && newEnd >= end) {
//            end = newEnd;
//        }
//        else if (newStart > end) {
//            mlong count = end - start + 1;
//
//            covered += count;
//
//            start = newStart;
//            end = newEnd;
//        }
//    }
//
//    covered += end - start + 1;
//
//    printf("%lld", covered);
//}
//
//void grafikExercise() {
//    mlong start, length;
//
//    std::vector<plong> events = std::vector<plong>();
//
//    while (scanf("%lld", &start) != EOF) {
//        scanf("%lld", &length);
//
//        events.push_back(plong(start, start + length));
//    }
//
//    std::sort(events.begin(), events.end(),
//        [](plong first, plong second) -> bool {
//            return first.second < second.second;
//        });
//
//    mlong attended = 0;
//
//    mlong currentTime = 1;
//
//    for (mlong i = 0; i < events.size(); i++) {
//        mlong startTime = events[i].first, endTime = events[i].second;
//
//        if (startTime >= currentTime) {
//            attended++;
//            currentTime = endTime;
//        }
//    }
//
//    printf("%lld", attended);
//}

void zeroSum() {

    mlong n;

    scanf("%lld", &n);

    if (n < 3) {
        printf("0");
        return;
    }

    std::vector<mlong> arr = std::vector<mlong>();

    for (mlong i = 0; i < n; i++) {
        mlong num;

        scanf("%lld", &num);
        arr.push_back(num);
    }

    std::sort(arr.begin(), arr.end());

    umlong pairs = 0;

    umlong lastPairs = 0;

    for (mlong i = 0; i < n - 1; i++) {
        mlong first = arr[i];

        /*if (i != 0 && arr[i] == arr[i - 1]) {
            pairs += repeatablePairs;
            continue;
        }*/

        lastPairs = 0;

        mlong left = i + 1, right = n - 1;

        //mlong debug = 10000 * 9999 * 9998 / 6;

        while (left < right) {
            mlong second = arr[left];
            mlong third = arr[right];

            mlong totalSum = second + third + first;

            if (totalSum > 0) {
                right--;

                if (right == i) right--;
            }
            else if (totalSum < 0) {
                left++;
            }
            else {

                bool areSame = second == third;

                //Get the count of same elements
                mlong countSecond = 1;
                mlong countThird = 1;
                umlong sharedCount = 0;

                if (!areSame) {
                    while (arr[left + countSecond] == second) {
                        countSecond++;
                    }

                    while (arr[right - countThird] == third) {
                        countThird++;
                    }
                }
                else {
                    sharedCount = right - left + 1;
                }
                
                umlong combinations = !areSame ? countSecond * countThird : sharedCount * (sharedCount - 1) / 2;

                //Debug
                //printf("%lld %lld %lld diff combinations are: %lld\n", first, second, third, combinations);
                lastPairs += combinations;
                //-10 -10 -8 -6 -5 13 15 18 18 18 20
                //-16 -10 -10 -10 -10 -8 -8 0 0 0 0 8 8 18 20 20 20 20 | 18
                //0 0 0 0 0 0 0 0 0 | 9
                //-20 -20 -10 -10 -10 -10 0 0 0 0 10 10 10 10 10 10 | 16


                if (areSame) break;
                else {
                    left += countSecond;
                    right -= countThird;
                }
            }
        }

        pairs += lastPairs;
    }

    printf("%llu", pairs);
}
int main()
{
    /*evilExercise();*/
    //grafikExercise();
    zeroSum(); //2 -5 2 3 -4 7 -4 0 1 -6
    // -6 -5 -4 -4 0 1 2 2 3
}
