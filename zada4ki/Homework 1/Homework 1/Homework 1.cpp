// Homework 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

typedef long long mlong;

mlong getMinSquareSide(mlong treeCoord, std::vector<mlong>& centerCoords) {

    //Get first element that is <= to treeCoord

    auto it = std::lower_bound(centerCoords.begin(), centerCoords.end(), treeCoord);

    //This is a special case if the tree coord is beyond all of the center coords
    if (it == centerCoords.end()) {
        mlong backwardCoord = *(--it);
        mlong backwardDiff = treeCoord - backwardCoord;

        return backwardDiff * 2;
    }
    //This is a special case if the tree coord is behind(below) all of the center coords
    else if (it == centerCoords.begin()) {
        mlong frontCoord = *it;
        mlong frontDiff = frontCoord - treeCoord;

        return frontDiff * 2;
    }

    mlong frontCoord = *it;
    mlong backwardCoord = *(--it);

    mlong frontDiff = frontCoord - treeCoord;
    mlong backwardDiff = treeCoord - backwardCoord;

    //Get the smaller of the 2 differences and multiply it by 2 to get the side of the square
    return std::min(frontDiff, backwardDiff) * 2;
}

mlong indexOfFirstBigger(mlong val, std::vector<mlong>& valArr) {

    mlong low = 0;
    mlong high = valArr.size() - 1;
    
    while (low < high) {

        mlong mid = (low + high) / 2;

        if (valArr[mid] <= val) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    return valArr[high] > val ? high : high + 1;
}

void homework() {
    mlong n, m;

    scanf("%lld", &n);
    scanf("%lld", &m);

    std::vector<mlong> centersX = std::vector<mlong>();
    std::vector<mlong> centersY = std::vector<mlong>();

    for (mlong i = 0; i < n; i++) {
        mlong x, y;

        scanf("%lld", &x);
        scanf("%lld", &y);

        centersX.push_back(x);
        centersY.push_back(y);
    }

    std::sort(centersX.begin(), centersX.end());
    std::sort(centersY.begin(), centersY.end());

    std::vector<mlong> treesMinSides = std::vector<mlong>();

    for (mlong i = 0; i < m; i++) {
        mlong x, y;

        scanf("%lld", &x);
        scanf("%lld", &y);

        mlong minSideFromX = getMinSquareSide(x, centersX);
        mlong minSideFromY = getMinSquareSide(y, centersY);

        mlong minSide = std::min(minSideFromX, minSideFromY);

        treesMinSides.push_back(minSide);
    }

    std::sort(treesMinSides.begin(), treesMinSides.end());

    mlong q;

    scanf("%lld", &q);

    for (mlong i = 0; i < q; i++) {
        mlong side;

        scanf("%lld", &side);

        //Use binary search to get the index of the first element that is bigger than side
        mlong countOfTrees = indexOfFirstBigger(side, treesMinSides);

        printf("%lld ", countOfTrees);
    }
}

int main()
{
    homework();
}

