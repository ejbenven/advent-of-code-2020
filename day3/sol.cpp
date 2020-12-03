#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <unordered_set>

using std::string;
using std::cout;
using std::endl;

std::unordered_set<unsigned int> locateTrees(string line);

struct slope_param_t {
    unsigned int pos;
    unsigned int right;
    unsigned int down;
    unsigned int treeCnt;
};

int main() {
    std::ifstream input;
    input.open("day3/input.txt");

    std::string line;
    std::array<slope_param_t, 5> slopes {{
        {0, 1, 1, 0},
        {0, 3, 1, 0},
        {0, 5, 1, 0},
        {0, 7, 1, 0},
        {0, 1, 2, 0}
    }};
    auto lineCnt = 0;
    while(std::getline(input, line)) {
        auto row = locateTrees(line);
        for(auto it = slopes.begin(); it != slopes.end(); it++) {
            if (lineCnt % it->down != 0) {
                continue;
            }
            it->treeCnt += row.contains(it->pos) ? 1 : 0;
            it->pos = (it->pos + it->right) % line.size();
        }
        lineCnt += 1;
    }

    unsigned long mult = 1;
    for(auto slope : slopes) {
        cout << "Collide with " << slope.treeCnt << " tree(s)" << endl;
        mult *= slope.treeCnt;
    }

    cout << "Multiplied give " << mult << endl;

    input.close();
    return 0;
}

std::unordered_set<unsigned int> locateTrees(string line)
{
    std::unordered_set<unsigned int> ans{};

    for(auto i = 0; i < line.size(); i++) {
        if (string(1, line[i]) == "#") {
            ans.insert(i);
        }
    }

    return ans;
}
