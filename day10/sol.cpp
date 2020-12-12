#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;



int main() {
    std::ifstream input;
    input.open("day10/input.txt");
    //input.open("day10/test_input.txt");

    string line;
    std::vector<unsigned int> joltages;
    while(std::getline(input, line)) {
        joltages.push_back(std::stoul(line));
    }
    input.close();

    std::sort(joltages.begin(), joltages.end());

    joltages.insert(joltages.begin(), 0);
    joltages.insert(joltages.end(), joltages.back() + 3);
    std::unordered_map<unsigned int, unsigned int> counts{ {0, 0}, {1, 0}, {2, 0}, {3, 0}};

    for (auto i = 0; i < joltages.size() - 1; i++) {
        auto diff = joltages[i + 1] - joltages[i];

        counts[diff] += 1;
    }

    cout << counts[1] * counts[3] << endl;

    return 0;
}
