// BinarySearchExercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

typedef long long mlong;
typedef unsigned long long umlong;
typedef std::pair<umlong, umlong> interval;

mlong n;
umlong l, d, curX, a, b;

umlong getLeft(umlong x) {
    if (x < d) return 0ULL;

    return x - d;
}

umlong getRight(mlong x) {
    if (x + d > l) return l;

    return x + d;
}

int main()
{
    scanf("%lld %llu %llu", &n, &l, &d);
    scanf("%llu %llu %llu", &curX, &a, &b);

    std::set<umlong> centers = std::set<umlong>();

    umlong coveredIntervals = 0;
    umlong desiredIntervals = l - d + 1;

    for (mlong i = 0; i < n; i++) {
        //Xi = (Xi-1 * A + B) % (L + 1).

        if (i != 0) {
            curX = (curX * a + b) % (l + 1);
        }

        centers.insert(curX);

        //Get the first center that is to the right of the currently added one
        auto firstRight = std::upper_bound(centers.begin(), centers.end(), curX);

        auto firstRightCopy = firstRight;

        //If the first right center is <= d distance to the curX, then search for all the centers that are <= d distance to the curX
        if (firstRight != centers.end()) {

            while (firstRight != centers.end() && (*firstRight) <= curX + d) {
                umlong distance = (*firstRight) - curX;

                coveredIntervals += distance * 2;

                firstRight++;
            }

            //First element that is > d distance away from curX
            /*auto lastRight = std::upper_bound(firstRight, centers.end(), curX, [](umlong val, umlong el) -> bool {
                return val + d < el;
            });*/

            //Iterate through all the elements and find the number of exclusive intervals
            /*while (firstRight != lastRight) {
                umlong distance = (*firstRight) - curX;

                desiredIntervals += distance * 2;

                firstRight++;
            }*/
        }
        else {

        }

        firstRightCopy--;

        while ((*firstRightCopy) + d >= curX) {
            umlong distance = curX - (*firstRightCopy);

            coveredIntervals += distance * 2;

            if (firstRightCopy == centers.begin()) {
                break;
            }

            firstRightCopy--;
        }

        if (coveredIntervals == desiredIntervals) {
            printf("%lld", i);
            return 0;
        }
    }

    printf("%s", "-1");
}