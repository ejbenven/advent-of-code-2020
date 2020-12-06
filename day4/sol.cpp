#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "absl/strings/str_split.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

bool validate(vector<string> lines);
unordered_map<string, string> parseInput(vector<string> lines);

int main() {
    std::ifstream input;
    input.open("day4/input.txt");


    string line;
    vector<string> lines{};
    auto validCnt = 0;
    while(std::getline(input, line)) {
        if (line == "" and lines.size() != 0) {
            if(validate(lines)) {
                validCnt += 1;
            }
            lines.clear();
        } else if (line != "") {
            lines.push_back(line);
        }
    }
    if(not (lines.size() == 0)) {
        if (validate(lines)) {
            validCnt += 1;
        }
    }

    cout << validCnt << " valid passport(s)" << endl;

}

bool validate(vector<string> lines)
{
    vector<string> mandatoryFields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", };
    vector<string> optionalFields = { "cid", };

    auto keys = parseInput(lines);
    for (auto field : mandatoryFields) {
        if (not keys.contains(field)) {
            return false;
        }
    }
    return true;
}

unordered_map<string, string> parseInput(vector<string> lines)
{
    unordered_map<string, string> passport{};

    for (auto line : lines) {
        if (line == "")
            cout << "ERROR" << endl;
        auto entries = absl::StrSplit(line, " ");
        for (auto entry : entries) {
            passport.insert(absl::StrSplit(entry, ":"));
        }
    }

    return passport;
}
