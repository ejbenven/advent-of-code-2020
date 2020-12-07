#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;

struct seat_t {
    unsigned int row;
    unsigned int col;
};

seat_t parse(string line);
unsigned int toIdx(string charIdx, int pow, string indicators);

int main() {
    std::ifstream input;
    input.open("day5/input.txt");


    string line;
    unsigned int maxId = 0;
    while(std::getline(input, line)) {
        auto seat = parse(line);
        auto id = seat.row * 8 + seat.col;
        maxId = std::max(id, maxId);
    }

    cout << "maxId: " << maxId << endl;

    return 0;
}

seat_t parse(string line)
{
    auto row = line.substr(0, 7);
    auto col = line.substr(7, 3);

    seat_t ans;
    ans.row = toIdx(row, 7, "BF");
    ans.col = toIdx(col, 3, "RL");

    return ans;
}

unsigned int toIdx(string charIdx, int pow, string indicators)
{
    unsigned int low = 0;
    unsigned int high = (1 << pow) - 1;
    for (auto i = 0; i < pow; i++) {
        auto modifier = 1 << (pow - i - 1);
        if (charIdx[i] == indicators[0]) {
            low += modifier;
        } else {
            high -= modifier;
        }
    }

    return low;
}

