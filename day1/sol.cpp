#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <tuple>

std::tuple<bool, unsigned int, unsigned int> reach_target(unsigned int target, std::unordered_set<unsigned int> &numbers);

int main() {
    std::ifstream input;
    input.open("day1/input.txt");

    std::unordered_set<unsigned int> numbers;
    std::string line;
    while(std::getline(input, line)) {
        numbers.insert(std::stoul(line));
    }

    //Part 1
    {
        auto ans = reach_target(2020, numbers);
        if(std::get<0>(ans)){
            std::cout << std::get<1>(ans) << " * " << std::get<2>(ans) << " = " << std::get<1>(ans) * std::get<2>(ans) << std::endl;
        }
    }

    //Part 2
    auto numbers_cpy = numbers;
    for(auto num : numbers) {
        auto search = numbers_cpy.find(num);
        numbers_cpy.erase(search);
        auto ans = reach_target(2020 - num, numbers_cpy);
        if(std::get<0>(ans)) {
            std::cout << std::get<1>(ans) << " * " << std::get<2>(ans) << " * " << num << " = " << std::get<1>(ans) * std::get<2>(ans) * num << std::endl;
            break;
        }
        numbers_cpy.insert(num);
    }

    input.close();
    return 0;
}

std::tuple<bool, unsigned int, unsigned int> reach_target(unsigned int target, std::unordered_set<unsigned int> &numbers)
{
    for (auto num : numbers) {
        auto search = numbers.find(target - num);
        if(search != numbers.end()) {
            return std::make_tuple(true, num, target - num);
        }
    }
    return std::make_tuple(false, 0, 0);
}
