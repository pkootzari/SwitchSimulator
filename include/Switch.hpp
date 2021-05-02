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

constexpr int DISCONNECTED = 0;
constexpr int INACTIVE = 1;
constexpr int ACTIVE  = 2;

class Switch {
    private:
        int numOfPorts;
        int id;
        std::string directory;
        std::vector<int> port_input_pipes;
        std::map<int, int> port_pipe_towrite;
        std::map<int, int> ports_status;
        std::map<int, int> lookup_table;
        fd_set readFDs;
    public:
        Switch(int numOfPorts, int id);
        void run(int read_fd_pipe);
};

#endif