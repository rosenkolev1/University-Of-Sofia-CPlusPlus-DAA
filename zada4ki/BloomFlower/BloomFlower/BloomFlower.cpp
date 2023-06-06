// BloomFlower.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lengthOfLongestSubstring(string s) {
    int substringStartInd = 0;

    string maxSubstring = "";
    int maxLengthSubstring = -1;

    string substring = "";

    for (int i = 0; i < s.size(); i++) {
        char curChar = s[i];

        int charCount = std::count(substring.begin(), substring.end(), curChar);

        if (charCount != 0) {

            int indexOfRepeated = substring.find(curChar);

            if (substring.size() > maxLengthSubstring || maxLengthSubstring < 0) {
                maxLengthSubstring = substring.size();
                maxSubstring = substring;
            }

            substring.erase(0, indexOfRepeated + 1);
            substring.push_back(curChar);
        }
        else {
            substring.push_back(curChar);
        }      
    }

    if (substring.size() > maxLengthSubstring || maxLengthSubstring < 0) {
        maxLengthSubstring = substring.size();
        maxSubstring = substring;
    }

    return maxLengthSubstring >= 0 ? maxLengthSubstring : 0;
}

int main()
{
    //vector<int> testCase = vector<int>();

    ////"abcabcbb"
    //
    //testCase.push_back(3);
    //testCase.push_back(2);
    //testCase.push_back(3);

    //vector<int> haha = twoSum(testCase, 6);

    //for (int i = 0; i < haha.size(); i++) {
    //    cout << haha[i] << " ";
    //}

    string testCase = "pwwkew";

    int longestThing = lengthOfLongestSubstring(testCase);

    cout << longestThing;
}
