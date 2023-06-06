// kontrolno1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>

typedef long long mlong;
typedef unsigned long long umlong;

void flowers() {

    umlong n, k;

    scanf("%llu %llu", &n, &k);

    std::vector<umlong> flowerPrices = std::vector<umlong>();

    for (umlong i = 0; i < n; i++) {
        umlong flowerPrice;

        scanf("%llu", &flowerPrice);

        flowerPrices.push_back(flowerPrice);
    }

    std::sort(flowerPrices.begin(), flowerPrices.end(), [](umlong first, umlong second) -> bool {
        return first > second;
    });

    umlong totalPrice = 0;

    for (umlong i = 0; i < n; i++) {
        umlong price = flowerPrices[i];
        umlong multiple = i / k + 1;

        price *= multiple;

        //if (multiple > 0) price *= multiple;

        totalPrice += price;
    }

    printf("%llu", totalPrice);

}

void shots() {
    umlong n;

    scanf("%llu", &n);

    //if (n == 1) {
    //    printf("%s", "0");
    //    return;
    //}

    std::vector<umlong> shots = std::vector<umlong>();

    for (umlong i = 0; i < n; i++) {
        umlong shotAlc;
        
        scanf("%llu", &shotAlc);
        
        shots.push_back(shotAlc);
    }

    if (n == 1) {
        printf("%s", "0");
        return;
    }

    //Two pointers
    umlong leftTotal = shots.front(), rightTotal = shots.back(), totalShots = 2, leftInd = 1, rightInd = n - 2;
    umlong maxTotal = leftTotal == rightTotal ? totalShots : 0;

    while (leftInd <= rightInd) {
        umlong leftShot = shots[leftInd];
        umlong rightShot = shots[rightInd];

        if (leftTotal < rightTotal) {
            totalShots++;
            leftTotal += leftShot;
            leftInd++;
        }
        else if (leftTotal > rightTotal) {
            totalShots++;
            rightTotal += rightShot;
            rightInd--;
        }

        if (leftTotal == rightTotal) {
            maxTotal = totalShots;

            totalShots++;
            leftTotal += shots[leftInd++];
            //leftInd++;
        }

        //1 1 3 1 2 2
        //1 3 1 1 | 2 1 3 3 | 4 2
        //1 3 1 1 2 1 3 3 4 2
    }

    printf("%llu", maxTotal);
}

void popcorn() {

    umlong n, k, s;

    scanf("%llu %llu %llu", &n, &k, &s);

    std::vector<umlong> packets = std::vector<umlong>();

    umlong totalCorn = 0;
    umlong biggestPacket = 0;

    for (umlong i = 0; i < n; i++) {
        umlong corn;
        
        scanf("%llu", &corn);

        totalCorn += corn;

        if (corn > biggestPacket) {
            biggestPacket = corn;
        }

        packets.push_back(corn);
    }

    if (k >= n) {
        umlong seconds = biggestPacket % s == 0 ? biggestPacket / s : biggestPacket / s + 1;

        printf("%llu", seconds);
    }

    std::vector<mlong> lines = std::vector<mlong>();

    std::vector<umlong> personsCorns = std::vector<umlong>();

    personsCorns.push_back(totalCorn);

    for (umlong i = 1; i < k; i++) {
        personsCorns.push_back(0);
        lines.push_back(n);
    }

    umlong maxInd = 0;

    umlong totalSeconds = totalCorn % s == 0 ? totalCorn / s : totalCorn / s + 1;

    while (maxInd != k - 1) {
        umlong maxCorn = personsCorns[maxInd];

        umlong nextCorn = personsCorns[maxInd + 1];

        umlong maxCornEnd = lines[maxInd];
        umlong nextCornEnd = maxInd + 1 >= lines.size() ? n : lines[maxInd + 1];

        umlong maxLostCorn = packets[maxCornEnd - 1];
        personsCorns[maxInd] -= maxLostCorn;
        personsCorns[maxInd + 1] += maxLostCorn;

        lines[maxInd]--;

        //Get max person
        umlong nextMaxCorn = 0;

        for (umlong i = 0; i < personsCorns.size(); i++) {
            if (nextMaxCorn <= personsCorns[i]) {
                nextMaxCorn = personsCorns[i];
                maxInd = i;
            }
        }

        umlong newTotalSeconds = personsCorns[maxInd] % s == 0 ? personsCorns[maxInd] / s : personsCorns[maxInd] / s + 1;

        if (totalSeconds > newTotalSeconds) {
            totalSeconds = newTotalSeconds;
        }
    }

    //1000 500 700 800 300 200 | | |
    //1000 500 700 800 300 | 200 | |
    //1000 500 700 800 | 300 200 | |
    //1000 500 700 | 800 300 200 | |
    //1000 500 | 700 800 300 200 | |
    //1000 500 | 700 800 300 | 200 |
    //1000 500 | 700 800 | 300 200 |
    //1000 | 500 700 800 | 300 200 |
    //1000 | 500 700 | 800 300 200 |

    printf("%llu", totalSeconds);
}

int main()
{
    //flowers();

    //shots();

    popcorn();
}
