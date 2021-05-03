#include "Manager.hpp"
#include "System.hpp"
#include "Switch.hpp"

using namespace std;

constexpr char ADD_SYSTEM[] = "MySystem";
constexpr char ADD_SWITCH[] = "MySwitch";
constexpr char CONNECT[] = "connect";
constexpr char PING[] = "ping";

void Manager::handleCommand() {
    string command;
    const int command_index = 0;
    while (getline(cin, command)) {
        vector<string> arguments = tokenizeInput(command);

        if(arguments[command_index] == ADD_SYSTEM) {
            if(arguments.size() != 2) {
                cout << "too few or too many arguments!\n";
                continue;
            }
            addSystem(stoi(arguments[1]));
        } else if(arguments[command_index] == ADD_SWITCH) {
            if(arguments.size() != 3) {
                cout << "too few or too many arguments!\n";
                continue;
            }
            addSwitch(stoi(arguments[1]), stoi(arguments[2]));
        } else if(arguments[command_index] == CONNECT) {
            if(arguments.size() != 4) {
                cout << "too few or too many arguments!\n";
                continue;
            }
            connect(stoi(arguments[1]), stoi(arguments[2]), stoi(arguments[3]));
        } else if(arguments[command_index] == PING) {
            if(arguments.size() != 3) {
                cout << "too few or too many arguments!\n";
                continue;
            }
            ping(stoi(arguments[1]), stoi(arguments[2]));
        } else {
            cout << "Unknown command!" << endl;
        }

        sleep(2);
    }
    sleep(5);
}

void Manager::addSwitch(int numOfPorts, int id) {
    if(find_switch_index(id) != -1) {
        cout << "switch with this id already exists!\n";
        return;
    }
    
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
    if(find_system_index(id) != -1) {
        cout << "system with this id already exists!\n";
        return;
    }

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

int Manager::find_system_index(int id) {
    int i;
    for(i = 0; i < systems.size(); i++)
        if(systems[i]->sy->getID() == id)
            return i;
    return -1;
}

int Manager::find_switch_index(int id) {
    int i;
    for(i = 0; i < switches.size(); i++)
        if(switches[i]->sw->getID() == id)
            return i;
    return -1;
}

void Manager::connect(int system_id, int switch_id, int port) {
    if(find_system_index(system_id) == -1) {
        cout << "system doesn't exist!\n";
        return;
    }
    if(find_switch_index(switch_id) == -1) {
        cout << "switch doesn't exist!\n";
        return;
    }
    if(switches[find_switch_index(switch_id)]->sw->getNumOfPorts() <= port) {
        cout << "this switch doesn't have a port with this number\n";
        return;
    }
    
    string switch_pipe = "switch" + to_string(switch_id) + "/port" + to_string(port);
    string system_pipe = "system" + to_string(system_id) + "/input";
    string msg_to_system = "connect " + switch_pipe;
    string msg_to_switch = "connect " + to_string(port) + " " + system_pipe;

    write(systems[find_system_index(system_id)]->pipes[1], msg_to_system.c_str(), msg_to_switch.length()+1);
    write(switches[find_switch_index(switch_id)]->pipes[1], msg_to_switch.c_str(), msg_to_switch.length()+1);
}

void Manager::ping(int from, int to) {
    if((find_system_index(from) == -1) || (find_system_index(to) == -1)) {
        cout << "system with this id doesn't exists!\n";
        return;
    }

    string command = "ping " + to_string(to);
    write(systems[find_system_index(from)]->pipes[1], command.c_str(), command.length()+1);
}

vector<string> Manager::tokenizeInput(string input) {
    stringstream inputStringStream(input);
    return vector<string>(istream_iterator<string>(inputStringStream),
                          istream_iterator<string>());
}