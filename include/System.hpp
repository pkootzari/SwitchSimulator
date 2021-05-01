#ifndef HEADER_SYSTEM
#define HEADER_SYSTEM

#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <iostream>

class System {
    private:
        int id;
    public:
        System(int id);
};

#endif