#include "Manager.hpp"
#include "System.hpp"
#include "Switch.hpp"

using namespace std;

constexpr char ADD_SYSTEM[] = "MySystem";
constexpr char ADD_SWITCH[] = "MySwitch";

void Manager::handleCommand() {
    string command;
    const int command_index = 0;
    while (getline(cin, command)) {
        vector<string> arguments = tokenizeInput(command);

        if(arguments[command_index] == ADD_SYSTEM)
            addSystem(stoi(arguments[1]));
        else if(arguments[command_index] == ADD_SWITCH)
            addSwitch(stoi(arguments[1]), stoi(arguments[2]));
    }
}

void Manager::addSwitch(int numOfPorts, int id) {
    switches.push_back(new Switch(numOfPorts, id));
    cout << "Switch created!\n";
}

void Manager::addSystem(int id) {
    systems.push_back(new System(id));
    cout << "System created!\n";
}

vector<string> Manager::tokenizeInput(string input) {
    stringstream inputStringStream(input);
    return vector<string>(istream_iterator<string>(inputStringStream),
                          istream_iterator<string>());
}