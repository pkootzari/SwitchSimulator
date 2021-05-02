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
        else
            write(switches[0]->pipes[1], "this is your last chance!", sizeof("this is your last chance!")); // for testing pipes
    }
}

void Manager::addSwitch(int numOfPorts, int id) {
    SwitchInfo* new_si = new SwitchInfo;
    Switch* new_switch = new Switch(numOfPorts, id);
    if(pipe(new_si->pipes) < 0)
        cout << "can't make unnamed pipes for switch " << id << endl;
    new_si->sw = new_switch;
    switches.push_back(new_si);
    cout << "Switch created!\n";
    if(fork() == 0)
        new_switch->run(new_si->pipes[0]);
}

void Manager::addSystem(int id) {
    SystemInfo* new_sy = new SystemInfo;
    System* new_system = new System(id);
    if(pipe(new_sy->pipes) < 0)
        cout << "can't make unnamed pipes for system " << id << endl;
    new_sy->sy = new_system;
    systems.push_back(new_sy);
    cout << "System created!\n";
    if(fork() == 0)
        new_system->run(new_sy->pipes[0]);
}

vector<string> Manager::tokenizeInput(string input) {
    stringstream inputStringStream(input);
    return vector<string>(istream_iterator<string>(inputStringStream),
                          istream_iterator<string>());
}