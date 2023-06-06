// CountSortExercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

//vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
//    int countArr[1001];
//
//    for (int i = 0; i < 1001; i++) {
//        countArr[i] = 0;
//    }
//
//    for (int i = 0; i < arr1.size(); i++) {
//        countArr[arr1[i]] += 1;
//    }
//
//    vector<int> finalArr = vector<int>();
//
//    //Get the elements from arr2 first
//    for (int i = 0; i < arr2.size(); i++) {
//        for (int y = 0; y < countArr[arr2[i]]; y++) {
//            finalArr.push_back(arr2[i]);
//        }
//
//        countArr[arr2[i]] = 0;
//    }
//
//    //Get the elements from the rest of arr1 in ascending order (not stable)
//    for (int i = 0; i < 1001; i++) {
//        for (int y = 0; y < countArr[i]; y++) {
//            finalArr.push_back(i);
//        }
//    }
//
//    return finalArr;
//}

//void bazinga() {
//    std::string bazinga = "bazinga";
//
//    std::string text;
//
//    getline(std::cin, text);
//
//    int countArr[256] = {};
//
//    for (int i = 0; i < text.size(); i++) {
//        countArr[tolower(text[i])]++;
//    }
//
//    int minLen = 1001;
//
//    for (int i = 0; i < bazinga.size(); i++) {
//
//        int letterCount = bazinga[i] != 'a' ? countArr[bazinga[i]] : countArr[bazinga[i]] / 2;
//
//        if (minLen > letterCount) minLen = letterCount;
//    }
//
//    std::cout << minLen;
//}

int main()
{
   
}
