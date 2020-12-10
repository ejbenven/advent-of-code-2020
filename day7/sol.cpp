#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "absl/strings/str_split.h"

using std::string;
using std::cout;
using std::endl;
using std::unordered_map;
using std::unordered_set;
using std::vector;

unordered_map<string, string> parse(string line);
unsigned int dfs(string node,
        unordered_map<string, vector<string>>& adjList,
        unordered_set<string>& visited);

int main() {
    std::ifstream input;
    input.open("day7/input.txt");

    string line;
    unordered_map<string, vector<string>> containedBy{};
    while(std::getline(input, line)) {
        auto relation = parse(line);

        for (auto p : relation) {
            if (containedBy.contains(p.first)) {
                containedBy[p.first].push_back(p.second);
            } else {
                containedBy.insert({p.first, vector<string>{{p.second}}});
            }
        }
    }

    unordered_set<string> visited = {"shiny gold bags"};

    cout << dfs("shiny gold bags", containedBy, visited) << " bags can contain at least one shiny gold bag" << endl;

    input.close();

    return 0;
}

unordered_map<string, string> parse(string line)
{
    unordered_map<string, string> ans{};
    vector<string> tmp = absl::StrSplit(line, " contain ");
    auto dest = tmp[0];
    vector<string> start = absl::StrSplit(tmp[1], ", ");

    for (auto i = 0; i < start.size(); i++) {
        vector<string> split = absl::StrSplit(start[i], " ");
        string id = split[1] + " " + split[2] + " bags";

        start[i] = id;

        ans.insert({id, dest});
    }
    return ans;
}

unsigned int dfs(string node,
        unordered_map<string, vector<string>>& adjList,
        unordered_set<string>& visited)
{
    unsigned int count = 0;

    for (auto bag : adjList[node]) {
        if (not visited.contains(bag)) {
            visited.insert(bag);
            count += 1;
            count += dfs(bag, adjList, visited);
        }
    }

    return count;
}
