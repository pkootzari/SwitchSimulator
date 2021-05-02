#ifndef HEADER_SYSTEM
#define HEADER_SYSTEM

#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>

class System {
    private:
        int id;
        std::string directory;
        int input_pipe;
    public:
        System(int id);
        void run(int read_fd_pipe);
};

#endif