#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

struct Person {

    std::string name;
    long fn;
    unsigned long long points;

    Person(std::string name, long fn, unsigned long long points) {
        this->name = name;
        this->fn = fn;
        this->points = points;
    }

    bool operator<(const Person& other) {
        if (points == other.points) {
            return fn < other.fn;
        }
        return points < other.points;
        if (this->points > other.points) return false;
        else if (this->points < other.points) return true;
        else {
            if (this->fn > other.fn) return false;
            else return true;
        }
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    unsigned long long n, q;

    std::vector<Person> people = std::vector<Person>();
    std::vector<unsigned long long> targetPoints = std::vector<unsigned long long>();

    std::cin >> n;
    std::cin >> q;

    for (unsigned long long i = 0; i < n; i++) {
        std::string name;
        long fn;
        unsigned long long points;

        std::cin >> name;
        std::cin >> fn;
        std::cin >> points;

        auto person = Person(name, fn, points);

        people.push_back(person);
    }

    for (unsigned long long i = 0; i < q; i++) {
        unsigned long long points;

        std::cin >> points;

        targetPoints.push_back(points);
    }

    std::sort(people.begin(), people.end());

    for (unsigned long long i = 0; i < q; i++) {
        unsigned long long curTarget = targetPoints[i];

        /*long long left = 0, right = people.size() - 1;

        while (left <= right) {
            long long midInd = (left + right) / 2;

            auto mid = people[midInd];

            if (mid.points < curTarget) {
                left = midInd + 1;
            }
            else {
                right = midInd - 1;
            }
        }*/

        auto targetPerson = *std::lower_bound(people.begin(), people.end(), Person("", -1, curTarget));

        std::cout << targetPerson.name << " " << targetPerson.fn << std::endl;
    }
}