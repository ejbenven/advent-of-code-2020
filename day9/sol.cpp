#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <deque>

using std::string;
using std::cout;
using std::endl;
using std::unordered_map;
using std::deque;
using std::vector;

bool validate(unordered_map<long int, long int> & counts, long int target);

int main() {
    std::ifstream input;
    input.open("day9/input.txt");
    //input.open("day9/test_input.txt");

    string line;
    unordered_map<long int, long int> counts;
    deque<long int> window;
    const unsigned int windowSize = 25;
    long int target;
    bool found = false;
    vector<long int> numbers;
    while(std::getline(input, line)) {
        auto num = std::stol(line);
        numbers.push_back(num);

        if (not found and window.size() == windowSize and not validate(counts, num)) {
            cout << "First non-compliant number is " << num << endl;
            target = num;
            found = true;
        }

        window.push_front(num);
        if(counts.contains(num)) {
            counts[num] += 1;
        } else {
            counts.insert({num, 1});
        }

        if(window.size() > windowSize) {
            num = window.back();
            window.pop_back();
            counts[num] -= 1;

            if (counts[num] == 0) {
                counts.erase(num);
            }
        }
    }

    input.close();

    window.clear();
    long int sum = 0;
    for (auto n : numbers) {
        sum += n;
        window.push_front(n);

        while (sum > target and window.size() > 0) {
            sum -= window.back();
            window.pop_back();
        }

        if (sum == target) {
            break;
        }
    }

    auto min = window.front();
    auto max = window.front();

    for (auto n : window) {
        min = std::min(min, n);
        max = std::max(max, n);
    }

    cout << "Encryption weakness " << min + max << endl;

    return 0;
}

bool validate(unordered_map<long int, long int> & counts, long int target)
{
    for(const auto item : counts) {
        auto remainder = target - item.first;
        if (remainder == item.first and item.second > 1) {
            return true;
        } else if (counts.contains(remainder) and counts[remainder] > 0) {
            return true;
        }
    }

    return false;
}
