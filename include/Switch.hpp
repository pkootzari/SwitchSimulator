#ifndef HEADER_SWITCH
#define HEADER_SWITCH

#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <fstream>
#include <sstream>
#include <iterator>

constexpr int DISCONNECTED = 0;
constexpr int INACTIVE = 1;
constexpr int ACTIVE  = 2;

const std::string STATUS[] = {"disconnected", "inactive", "active"};

typedef struct port {
    int status;
    int input_pipe_fd;
    int output_pipe_fd;
} Port;

class Switch {
    private:
        int id;
        int numOfPorts;
        int MASSAGE_SIZE;
        std::ofstream log;
        std::string directory;
        // std::vector<int> port_input_pipes;
        // std::map<int, int> port_pipe_towrite;
        // std::map<int, int> ports_status;
        std::map<int, Port*> ports;
        std::map<int, int> lookup_table;
        // fd_set readFDs;
        void handleManagerCommand(int read_fd_pipe);
        void handleInputFrame(int port_num, int pipe_fd);
        void initiatePipes();
        std::vector<std::string> tokenizeInput(std::string input);
        void printPortStatus(int port);
    public:
        int getID();
        int getNumOfPorts();
        Switch(int numOfPorts, int id);
        void run(int read_fd_pipe);
};

#endif