#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;

enum state_t {
    FLOOR,
    EMPTY,
    OCCUPIED,
};

bool stable(const vector<vector<state_t>> & left, const vector<vector<state_t>> & right);
void update(vector<vector<state_t>> & newWorld, const vector<vector<state_t>> & prevWorld);
int countAdj(int i, int j, state_t state, const vector<vector<state_t>> & world);

void printW(const vector<vector<state_t>> & world)
{
    for (const auto& r : world) {
        for (auto c : r) {
            string out = c == FLOOR ? "." : c == EMPTY ? "L" : "#";
            cout << out;
        }
        cout << endl;
    }
}

int main() {
    std::ifstream input;
    input.open("day11/input.txt");
    //input.open("day11/test_input.txt");

    vector<vector<state_t>> world;
    string line;
    while(std::getline(input, line)) {
        vector<state_t> row(line.size());
        for (auto i = 0; i < line.size(); i++) {
            if (string(1, line[i]) == ".")      { row[i] = FLOOR; }
            else if (string(1, line[i]) == "L") { row[i] = EMPTY; }
            else                                { row[i] = OCCUPIED; }
        }
        world.push_back(row);
    }
    input.close();


    vector<vector<state_t>> worldCpy;
    do {
        worldCpy = world;
        update(world, worldCpy);
    } while(not stable(world, worldCpy));

    long int cnt = 0;
    for (const auto& r : world) {
        for (auto c : r) {
            cnt += c == OCCUPIED ? 1 : 0;
        }
    }

    cout << cnt << " occupied seats" << endl;

    return 0;
}

bool stable(const vector<vector<state_t>> & left, const vector<vector<state_t>> & right)
{
    for (auto i = 0; i < left.size(); i++) {
        for (auto j = 0; j < left[0].size(); j++) {
            if (left[i][j] != right[i][j]) {
                return false;
            }
        }
    }

    return true;
}

void update(vector<vector<state_t>> & newWorld, const vector<vector<state_t>> & prevWorld)
{
    for (auto i = 0; i < prevWorld.size(); i++) {
        for (auto j = 0; j < prevWorld[0].size(); j++) {
            auto occ = countAdj(i, j, OCCUPIED, prevWorld);
            if (prevWorld[i][j] == EMPTY and occ == 0) {
                newWorld[i][j] = OCCUPIED;
            } else if (prevWorld[i][j] == OCCUPIED and occ >= 4) {
                newWorld[i][j] = EMPTY;
            } else {
                newWorld[i][j] = prevWorld[i][j];
            }
        }
    }
}


int countAdj(int i, int j, state_t state, const vector<vector<state_t>> & world)
{
    int cnt = 0;
    for (auto x = i - 1; x <= i + 1; x++) {
        for (auto y = j - 1; y <= j + 1; y++) {
            if (x < 0 or y < 0 or x >= world.size() or y >= world[0].size() or (x == i and y == j)) {
                continue;
            }

            cnt += world[x][y] == state ? 1 : 0;
        }
    }

    return cnt;
}
