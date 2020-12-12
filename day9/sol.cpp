#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <deque>

using std::string;
using std::cout;
using std::endl;
using std::unordered_map;
using std::deque;

bool validate(unordered_map<int, int> & counts, int target);

int main() {
    std::ifstream input;
    input.open("day9/input.txt");
    //input.open("day9/test_input.txt");

    string line;
    unordered_map<int, int> counts;
    deque<int> window;
    const unsigned int windowSize = 25;
    while(std::getline(input, line)) {
        auto num = std::stoi(line);

        if (window.size() == windowSize && not validate(counts, num)) {
            cout << "First non-compliant number is " << num << endl;
            break;
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

    return 0;
}

bool validate(unordered_map<int, int> & counts, int target)
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
