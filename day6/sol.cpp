#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;
using std::unordered_set;

unordered_set<char> parse(string line);

int main() {
    std::ifstream input;
    input.open("day6/input.txt");


    string line;
    string group = "";
    auto counts = 0;
    while(std::getline(input, line)) {
        if(line == "" and group.size() != 0) {
            auto ans = parse(group);
            counts += ans.size();
            group = "";
        } else {
            group += line;
        }
    }

    if (group != "") {
        auto ans = parse(group);
        counts += ans.size();
        group = "";
    }

    cout << "sum: " << counts << endl;

    input.close();

    return 0;
}

unordered_set<char> parse(string line)
{
    unordered_set<char> ans{};

    for (auto c : line) {
        ans.insert(c);
    }

    return ans;
}

