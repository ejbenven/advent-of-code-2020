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
        virtual ~Operator() = default;
};

class Nop : public Operator {
    public:
        operator_var_t exec(operator_var_t input) override
        {
            input.line += 1;
            return input;
        }
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
    private:
        int jmp;
};




unique_ptr<Operator> parse(string line);

int main() {
    std::ifstream input;
    input.open("day8/input.txt");
    //input.open("day8/test_input.txt");

    string line;
    vector<unique_ptr<Operator>> program;
    while(std::getline(input, line)) {
        program.push_back(parse(line));
    }

    operator_var_t ptr = {0, 0};
    unordered_set<unsigned int> visited;

    while (not visited.contains(ptr.line)) {
        visited.insert(ptr.line);
        ptr = program[ptr.line]->exec(ptr);
    }

    cout << "Acc value = " << ptr.acc << endl;

    input.close();


    return 0;
}

unique_ptr<Operator> parse(string line)
{
    vector<absl::string_view> args = absl::StrSplit(line, " ");
    unique_ptr<Operator> ans;
    if(args[0] == "nop") {
        ans = std::make_unique<Nop>();
    } else if (args[0] == "acc") {
        int arg;
        (void)absl::SimpleAtoi(args[1], &arg);
        ans = std::make_unique<Acc>(arg);
    } else {
        int arg;
        (void)absl::SimpleAtoi(args[1], &arg);
        ans = std::make_unique<Jmp>(arg);
    }

    return ans;
}
