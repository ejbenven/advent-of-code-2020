#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;



int main() {
    std::ifstream input;
    input.open("day13/input.txt");
    //input.open("day13/test_input.txt");

    string line;
    std::getline(input, line);
    auto start = std::stoi(line);

    vector<int>ids;
    std::getline(input, line);
    vector<absl::string_view>idsStr = absl::StrSplit(line, ",");

    int bestId = 0;
    int bestTime = std::numeric_limits<int>::max();
    for (auto entry : idsStr) {
        if (entry == "x") { continue; }

        int id;
        (void)absl::SimpleAtoi(entry, &id);
        auto time = (start % id);
        if (time > 0) { time = id - time; }

        if (time < bestTime) {
            bestId = id;
            bestTime = time;
        }
    }
    input.close();

    cout << bestTime * bestId << endl;


    return 0;
}
