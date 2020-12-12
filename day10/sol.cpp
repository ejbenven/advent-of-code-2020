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
    std::vector<int> joltages;
    while(std::getline(input, line)) {
        joltages.push_back(std::stoul(line));
    }
    input.close();

    std::sort(joltages.begin(), joltages.end());

    joltages.insert(joltages.begin(), 0);
    joltages.insert(joltages.end(), joltages.back() + 3);
    std::unordered_map<int, int> counts{ {0, 0}, {1, 0}, {2, 0}, {3, 0}};

    for (auto i = 0; i < joltages.size() - 1; i++) {
        auto diff = joltages[i + 1] - joltages[i];

        counts[diff] += 1;
    }

    cout << counts[1] * counts[3] << endl;

    std::vector<long long int> arrangements(joltages.size(), 0);
    arrangements[arrangements.size()-1] = 1;

    for (int i = arrangements.size() - 1; i >= 0; i--) {
        int j = i - 1;
        while (j >= 0 and joltages[j] >= joltages[i] - 3) {
            arrangements[j] += arrangements[i];
            j--;
        }
    }

    cout << arrangements[0] << " arrangements in total" << endl;

    return 0;
}
