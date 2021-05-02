#include "System.hpp"

using namespace std;

System::System(int id) {
    this->id = id;
    this->directory = "System" + to_string(id);
    if(mkdir(directory.c_str(), 0777) == -1)
        cout << "System " << id << "can't make its directory!\n";

    string pipe_name = directory + "/in";
    if(mkfifo(pipe_name.c_str(), 0666) != 0) 
        cout << "failed to make pipe for system " << id << endl;
    open(pipe_name.c_str(), O_RDONLY | O_NONBLOCK);
}

void System::run(int read_fd_pipe) {

}