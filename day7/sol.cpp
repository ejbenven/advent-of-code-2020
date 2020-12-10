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

unordered_map<string, string> parseContained(string line);
unordered_map<string, vector<std::pair<unsigned int, string>>> parseContains(string line);
unsigned int dfsContained(string node,
        unordered_map<string, vector<string>>& adjList,
        unordered_set<string>& visited);
unsigned long int dfsContains(string node,
        unordered_map<string, vector<std::pair<unsigned int, string>>>& adjList);

int main() {
    std::ifstream input;
    input.open("day7/input.txt");

    string line;
    unordered_map<string, vector<string>> containedBy{};
    while(std::getline(input, line)) {
        auto relation = parseContained(line);

        for (auto p : relation) {
            if (containedBy.contains(p.first)) {
                containedBy[p.first].push_back(p.second);
            } else {
                containedBy.insert({p.first, vector<string>{{p.second}}});
            }
        }
    }

    unordered_set<string> visited = {"shiny gold bags"};

    cout << dfsContained("shiny gold bags", containedBy, visited) << " bags can contain at least one shiny gold bag" << endl;

    input.close();

    input.open("day7/input.txt");
    //input.open("day7/test_input.txt");

    unordered_map<string, vector<std::pair<unsigned int, string>>> contains{};
    while(std::getline(input, line)) {
        auto relation = parseContains(line);

        for (auto p : relation) {
            if (contains.contains(p.first)) {
                contains[p.first].insert(contains[p.first].end(), p.second.begin(), p.second.end());
            } else {
                contains.insert({p.first, p.second});
            }
        }
    }

    cout << "One shiny gold bag must contain " << dfsContains("shiny gold bags", contains) << " bags" << endl;

    input.close();


    return 0;
}

unordered_map<string, string> parseContained(string line)
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

unordered_map<string, vector<std::pair<unsigned int, string>>> parseContains(string line)
{
    vector<string> tmp = absl::StrSplit(line, " contain ");
    auto start = tmp[0];
    vector<string> dest = absl::StrSplit(tmp[1], ", ");
    unordered_map<string, vector<std::pair<unsigned int, string>>> ans{{start, vector<std::pair<unsigned int, string>>{}}};

    if (tmp[1] == "no other bags.") {
        return ans;
    }

    for (auto i = 0; i < dest.size(); i++) {
        vector<string> split = absl::StrSplit(dest[i], " ");
        string id = split[1] + " " + split[2] + " bags";

        ans[start].push_back(std::pair(std::stoul(split[0]), id));

    }
    return ans;
}

unsigned int dfsContained(string node,
        unordered_map<string, vector<string>>& adjList,
        unordered_set<string>& visited)
{
    unsigned int count = 0;

    for (auto bag : adjList[node]) {
        if (not visited.contains(bag)) {
            visited.insert(bag);
            count += 1;
            count += dfsContained(bag, adjList, visited);
        }
    }

    return count;
}

unsigned long int dfsContains(string node,
        unordered_map<string, vector<std::pair<unsigned int, string>>>& adjList
        )
{
    unsigned long int count = 0;

    for (auto bag : adjList[node]) {
        count += bag.first;
        count += bag.first * dfsContains(bag.second, adjList);
    }

    return count;
}
