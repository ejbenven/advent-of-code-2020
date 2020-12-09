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

    cout << "Part1: " << counts << endl;

    input.close();
    input.open("day6/input.txt");

    counts = 0;
    unordered_set<char> groupAns{};
    group = "";

    while(std::getline(input, line)) {
        if(line == "" and group.size() != 0) {
            counts += groupAns.size();
            groupAns.clear();
            group = "";
        } else if (group.size() == 0){
            group += line;
            groupAns = parse(line);
        } else {
            auto individualAns = parse(line);
            unordered_set<char> out;
            for (auto c : individualAns) {
                if (groupAns.contains(c)) {
                    out.insert(c);
                }
            }
            groupAns = out;
            group += line;
        }
    }

    if (group != "") {
        counts += groupAns.size();
        groupAns.clear();
        group = "";
    }

    cout << "Part 2: " << counts << endl;
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

