#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using std::string;
using std::vector;
using std::tuple;
using std::cout;
using std::endl;
using std::get;

struct password_tokens_t {
    char letter;
    tuple<unsigned int, unsigned int> minmax;
    string password;
};

password_tokens_t parse(string line);
vector<string> split(string line, string token);
bool validatePart1(password_tokens_t tokens);
bool validatePart2(password_tokens_t tokens);

int main() {
    std::ifstream input;
    input.open("input.txt");

    std::string line;
    auto validPassCnt = 0;
    while(std::getline(input, line)) {
        auto passwordTokens = parse(line);
        //validPassCnt += validatePart1(passwordTokens);
        validPassCnt += validatePart2(passwordTokens);
    }

    cout << validPassCnt << " valid password(s)" << endl;

    input.close();
    return 0;
}

bool validatePart1(password_tokens_t tokens)
{
    auto cnt = 0;

    for (auto c : tokens.password) {
        cnt += c == tokens.letter ? 1 : 0;
    }

    return (cnt >= get<0>(tokens.minmax)) and (cnt <= get<1>(tokens.minmax));
}

bool validatePart2(password_tokens_t tokens)
{
    return ((tokens.letter == tokens.password.at(get<0>(tokens.minmax) - 1)) or
        (tokens.letter == tokens.password.at(get<1>(tokens.minmax) - 1))) and
        (tokens.password.at(get<0>(tokens.minmax) - 1) != tokens.password.at(get<1>(tokens.minmax) - 1));
}

password_tokens_t parse(string line)
{
    password_tokens_t ret;

    auto spaceSplit = split(line, " ");
    auto minmax = split(spaceSplit.at(0), "-");

    ret.minmax = std::make_tuple(std::stoul(minmax.at(0)), std::stoul(minmax.at(1)));
    ret.letter = spaceSplit.at(1).at(0);
    ret.password = spaceSplit.at(2);

    return ret;
}

vector<string> split(string line, string token)
{
    vector<string> substrs;
    string currentSubstr = "";

    for (auto c : line) {
        if (token == string(1, c)) {
            substrs.push_back(currentSubstr);
            currentSubstr = "";
        } else {
            currentSubstr.push_back(c);
        }
    }
    if (currentSubstr != "")
        substrs.push_back(currentSubstr);

    return substrs;
}
