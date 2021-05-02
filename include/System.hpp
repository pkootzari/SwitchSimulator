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

class System {
    private:
        int id;
        std::string directory;
        int input_pipe;
        int write_to_switch;
        int MASSAGE_SIZE;
        void handleManagerCommand(int read_fd_pipe);
        void handleInputFrame(int input_pipe);
        void initiatePipes();
    public:
        int getID();
        System(int id);
        void run(int read_fd_pipe);
};

#endif