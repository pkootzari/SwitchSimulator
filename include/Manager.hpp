#ifndef HEADER_MANAGER
#define HEADER_MANAGER

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <unistd.h>
#include <map>

class Switch;
class System;

typedef struct SwtichInfo {
    Switch* sw;
    int pipes[2];
} SwitchInfo;

typedef struct SystemInfo {
    System* sy;
    int pipes[2];
} SystemInfo;

class Manager {
    private:
        std::vector<SwitchInfo*> switches;
        std::vector<SystemInfo*> systems;
        std::vector<std::string> tokenizeInput(std::string input);
        void addSwitch(int numOfPorts, int id);
        void addSystem(int id);
        void connect(int system_id, int switch_id, int port);
        int find_system_index(int id);
        int find_switch_index(int id);
    public:
        void handleCommand();
};

#endif