#include "System.hpp"

using namespace std;

System::System(int id) {
    this->MASSAGE_SIZE = 128;
    this->id = id;
    this->directory = "system" + to_string(id);
    this->write_to_switch = 0;
}

int System::getID() { return id; }

void System::initiatePipes() {
    if(mkdir(directory.c_str(), 0777) == -1)
        cout << "System " << id << "can't make its directory!\n";
    
    string pipe_name = directory + "/input";
    if(mkfifo(pipe_name.c_str(), 0666) != 0) 
        cout << "failed to make pipe for system " << id << endl;
    if( (this->input_pipe = open(pipe_name.c_str(), O_RDONLY | O_NONBLOCK) < 0) )
        cout << "faild to open the pipe for system " << id << endl;

    cout << "system " << id << " opend " << this->input_pipe << endl;
}

void System::run(int read_fd_pipe) {
    initiatePipes();

    fd_set inputs;
    int max_fd = 0; // felan estefadeii nadare in
    while (1) {
        FD_ZERO(&inputs);
        FD_SET(read_fd_pipe, &inputs);
        max_fd = read_fd_pipe;
        FD_SET(input_pipe, &inputs);
        if(max_fd < input_pipe)
            max_fd = input_pipe;

        if(select(1000, &inputs, NULL, NULL, NULL) < 0)
            cout << "select error in system " << id << endl;

        if(FD_ISSET(read_fd_pipe, &inputs)) {
            handleManagerCommand(read_fd_pipe);
        } else if(FD_ISSET(input_pipe, &inputs)) {
            handleInputFrame(input_pipe);
        }
    }
}

void System::handleManagerCommand(int read_fd_pipe) {
    char massage[MASSAGE_SIZE];
    read(read_fd_pipe, massage, MASSAGE_SIZE);
    cout << "for system " << id << " : " << massage << endl;
}

void System::handleInputFrame(int input_pipe) {
    char massage[MASSAGE_SIZE];
    read(input_pipe, massage, MASSAGE_SIZE);
    cout << "incoming frame for system " << id << " : " << massage << endl;
}