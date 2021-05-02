#ifndef HEADER_SYSTEM
#define HEADER_SYSTEM

#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

#define MASSAGE_SIZE 128

class System {
    private:
        int id;
        std::string directory;
        int input_pipe;
        int write_to_switch;
        void handleManagerCommand(int read_fd_pipe);
        void handleInputFrame(int input_pipe);
    public:
        System(int id);
        void run(int read_fd_pipe);
};

#endif