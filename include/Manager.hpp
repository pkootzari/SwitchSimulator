#ifndef HEADER_MANAGER
#define HEADER_MANAGER

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

class Switch;
class System;

class Manager {
    private:
        std::vector<Switch*> switches;
        std::vector<System*> systems;
        std::vector<std::string> tokenizeInput(std::string input);
        void addSwitch(int numOfPorts, int id);
        void addSystem(int id);
    public:
        void handleCommand();
};

#endif