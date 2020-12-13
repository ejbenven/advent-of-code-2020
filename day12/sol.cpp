#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <memory>

using std::string;
using std::cout;
using std::endl;
using std::unordered_set;
using std::unique_ptr;
using std::make_unique;
using std::vector;

struct ship_t {
    int x;
    int y;
    int alpha;
};

class Command {
    public:
        virtual ~Command()=default;
        virtual ship_t exec(ship_t ship) const=0;
};

class Move : public Command {
    public:
        Move(int x, int y) : x(x), y(y) {}

        ship_t exec(ship_t ship) const
        {
            ship.x += this->x;
            ship.y += this->y;

            return ship;
        }

    private:
        int x;
        int y;

};

class Rotate : public Command {
    public:
        Rotate(int alpha) : alpha(alpha) {}

        ship_t exec(ship_t ship) const
        {
            ship.alpha += this->alpha;
            ship.alpha %= 360;
            ship.alpha = ship.alpha < 0 ? ship.alpha + 360 : ship.alpha;

            return ship;
        }

    private:
        int alpha;

};

class Forward : public Command {
    public:
        Forward(int unit) : unit(unit) {}

        ship_t exec(ship_t ship) const
        {
            switch(ship.alpha) {
                case 0:
                    ship.x += this->unit;
                    break;
                case 90:
                    ship.y += this->unit;
                    break;
                case 180:
                    ship.x -= this->unit;
                    break;
                case 270:
                    ship.y -= this->unit;
                    break;
                default:
                    cout << "ERROR, unexpected angle: " << ship.alpha << endl;
            };

            return ship;
        }

    private:
        int unit;

};

unique_ptr<Command> parse(string line);

int main() {
    std::ifstream input;
    input.open("day12/input.txt");
    //input.open("day12/test_input.txt");

    string line;
    vector<unique_ptr<Command>> commands;
    while(std::getline(input, line)) {
        commands.push_back(parse(line));
    }
    input.close();

    ship_t ship = {0, 0, 0};
    for (const auto& command : commands) {
        ship = command->exec(ship);
    }

    cout << std::abs(ship.x) + std::abs(ship.y) << endl;

    return 0;
}

unique_ptr<Command> parse(string line)
{
    string id = string(1, line[0]);
    int arg = std::stoi(line.substr(1, line.size()-1));
    unique_ptr<Command> ans;

    if (id == "N") { ans = make_unique<Move>(0, arg); }
    else if (id == "S") { ans = make_unique<Move>(0, -arg); }
    else if (id == "E") { ans = make_unique<Move>(arg, 0); }
    else if (id == "W") { ans = make_unique<Move>(-arg, 0); }
    else if (id == "L") { ans = make_unique<Rotate>(arg); }
    else if (id == "R") { ans = make_unique<Rotate>(-arg); }
    else if (id == "F") { ans = make_unique<Forward>(arg); }
    else { cout << "unexpected cmd" << endl; }

    return ans;
}
