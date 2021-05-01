#ifndef HEADER_SWITCH
#define HEADER_SWITCH

#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <fcntl.h>

typedef struct port {
    bool open;
    int to_system_id;
    int port_number;
} port;

class Switch {
    private:
        int numOfPorts;
        int id;
        int read_pipe;
        int write_pipe;
        std::vector<port*> lookup;
    public:
        Switch(int numOfPorts, int id);
};

#endif