#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <memory>

#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"

using std::string;
using std::cout;
using std::endl;
using std::unordered_set;
using std::vector;
using std::unique_ptr;

struct operator_var_t {
    int acc;
    unsigned int line;
};

class Operator {
    public:
        virtual operator_var_t exec(operator_var_t input)=0;
        virtual std::pair<bool, operator_var_t> execOther(operator_var_t input)=0;
        virtual ~Operator() = default;
};

class Nop : public Operator {
    public:
        Nop (int val) { this->val = val; }
        operator_var_t exec(operator_var_t input) override
        {
            input.line += 1;
            return input;
        }
        std::pair<bool, operator_var_t> execOther(operator_var_t input) override
        {
            input.line += this->val;
            return std::make_pair(true, input);
        }
    private:
        int val;
};

class Acc : public Operator {
    public:
        Acc(int acc) { this->acc = acc; }
        operator_var_t exec(operator_var_t input) override
        {
            input.acc += this->acc;
            input.line += 1;
            return input;
        }

        std::pair<bool, operator_var_t> execOther(operator_var_t input) override
        {
            return std::make_pair(false, input);
        }
    private:
        int acc;
};

class Jmp : public Operator {
    public:
        Jmp (int jmp) { this->jmp = jmp; }
        operator_var_t exec(operator_var_t input) override
        {
            input.line += this->jmp;
            return input;
        }

        std::pair<bool, operator_var_t> execOther(operator_var_t input) override
        {
            input.line += 1;
            return std::make_pair(true, input);
        }
    private:
        int jmp;
};




unique_ptr<Operator> parse(string line);
std::pair<bool, operator_var_t> bugfix(const vector<unique_ptr<Operator>>& program,
        operator_var_t ptr, unordered_set<unsigned int>& visited, bool switched);

int main() {
    std::ifstream input;
    input.open("day8/input.txt");
    //input.open("day8/test_input.txt");

    string line;
    vector<unique_ptr<Operator>> program;
    while(std::getline(input, line)) {
        program.push_back(parse(line));
    }
    input.close();

    operator_var_t ptr = {0, 0};
    unordered_set<unsigned int> visited;

    while (not visited.contains(ptr.line)) {
        visited.insert(ptr.line);
        ptr = program[ptr.line]->exec(ptr);
    }

    cout << "Acc value = " << ptr.acc << endl;

    visited.clear();
    ptr = { 0, 0 };
    auto ans = bugfix(program, ptr, visited, false);

    if (not ans.first) {
        cout << "No solution was found" << endl;
    } else {
        cout << "Accumulator value at end of program is: " << ans.second.acc << endl;
    }


    return 0;
}

std::pair<bool, operator_var_t> bugfix(const vector<unique_ptr<Operator>>& program,
        operator_var_t ptr, unordered_set<unsigned int>& visited, bool switched)
{
    if (ptr.line < 0 or ptr.line > program.size() + 1 or visited.contains(ptr.line)) {
        return std::make_pair(false, ptr);
    } else if (ptr.line == program.size()) {
        return std::make_pair(true, ptr);
    }

    visited.insert(ptr.line);
    auto newPtr = program[ptr.line]->exec(ptr);
    auto res = bugfix(program, newPtr, visited, switched);

    if (res.first or switched) {
        return res;
    } else {
        auto fix = program[ptr.line]->execOther(ptr);

        if (not fix.first) {
            visited.erase(ptr.line);
            return res;
        } else {
            res = bugfix(program, fix.second, visited, true);
            visited.erase(ptr.line);
            return res;
        }
    }
}

unique_ptr<Operator> parse(string line)
{
    vector<absl::string_view> args = absl::StrSplit(line, " ");
    unique_ptr<Operator> ans;
    int arg;
    (void)absl::SimpleAtoi(args[1], &arg);
    if(args[0] == "nop") {
        ans = std::make_unique<Nop>(arg);
    } else if (args[0] == "acc") {
        ans = std::make_unique<Acc>(arg);
    } else {
        ans = std::make_unique<Jmp>(arg);
    }

    return ans;
}
