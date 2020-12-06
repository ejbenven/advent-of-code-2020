#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <regex>

#include "absl/strings/str_split.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;
using std::stoul;

bool validate1(vector<string> lines);
bool validate2(vector<string> lines);
unordered_map<string, string> parseInput(vector<string> lines);

int main() {
    std::ifstream input;
    input.open("day4/input.txt");


    string line;
    vector<string> lines{};
    auto validCnt = 0;
    while(std::getline(input, line)) {
        if (line == "" and lines.size() != 0) {
            //if(validate1(lines)) {
            if(validate2(lines)) {
                validCnt += 1;
            }
            lines.clear();
        } else if (line != "") {
            lines.push_back(line);
        }
    }
    if(not (lines.size() == 0)) {
        //if (validate1(lines)) {
        if (validate2(lines)) {
            validCnt += 1;
        }
    }

    cout << validCnt << " valid passport(s)" << endl;

}

bool validate2(vector<string> lines)
{
    vector<string> mandatoryFields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", };
    vector<string> optionalFields = { "cid", };

    auto keys = parseInput(lines);
    for (auto field : mandatoryFields) {
        if (not keys.contains(field)) {
            return false;
        }
    }

    for (const auto& item : keys) {
        if (item.first == "byr") {
            if (item.second.size() != 4 or (stoul(item.second) < 1920 or stoul(item.second) > 2002)) {
                return false;
            }
        } else if (item.first == "iyr") {
            if (item.second.size() != 4 or (stoul(item.second) < 2010 or stoul(item.second) > 2020)) {
                return false;
            }
        } else if (item.first == "eyr") {
            if (item.second.size() != 4 or (stoul(item.second) < 2020 or stoul(item.second) > 2030)) {
                return false;
            }
        } else if (item.first == "hgt") {
            if (item.second.size() < 4) {
                return false;
            }
            auto unitLength = 2;
            auto unit = item.second.substr(item.second.size() - unitLength, unitLength);
            auto data = stoul(item.second.substr(0, item.second.size() - unitLength));
            if (unit == "cm") {
                if (data < 150 or data > 193) {
                    return false;
                }
            } else if (unit == "in") {
                if (data < 59 or data > 76) {
                    return false;
                }
            } else {
                return false;
            }
        } else if (item.first == "hcl") {
            std::smatch base_match{};
            if (not std::regex_match(item.second, base_match, std::regex("^#[a-f_0-9]{6}$"))) {
                return false;
            }
        } else if (item.first == "ecl") {
            std::unordered_set<string> eyeColors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth",};
            if (not eyeColors.contains(item.second)) {
                return false;
            }
        } else if (item.first == "pid") {
            std::smatch base_match{};
            if (not std::regex_match(item.second, base_match, std::regex("^[0-9]{9}$"))) {
                return false;
            }
        }else if (item.first != "cid") {
            return false;
        }
    }

    return true;
}

bool validate1(vector<string> lines)
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
