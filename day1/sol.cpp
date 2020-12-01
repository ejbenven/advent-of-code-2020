#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

bool reach_target(unsigned int target, std::unordered_set<unsigned int> &numbers);

int main() {
    std::ifstream input;
    input.open("input.txt");

    std::unordered_set<unsigned int> numbers;
    std::string line;
    while(std::getline(input, line)) {
        numbers.insert(std::stoul(line));
    }

    reach_target(2020, numbers);

    input.close();
    return 0;
}

bool reach_target(unsigned int target, std::unordered_set<unsigned int> &numbers)
{
    for (auto num : numbers) {
        auto search = numbers.find(target - num);
        if(search != numbers.end()) {
            std::cout << "Results " << num << " " << target - num << std::endl;
            std::cout << "Multiplied = " << num * (target - num) << std::endl;
            return true;
        }
    }
    return false;
}
