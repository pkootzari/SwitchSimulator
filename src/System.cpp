#include "System.hpp"

using namespace std;

System::System(int id) {
    this->id = id;
    this->directory = "System" + to_string(id);
    this->write_to_switch = 0;
    if(mkdir(directory.c_str(), 0777) == -1)
        cout << "System " << id << "can't make its directory!\n";

    string pipe_name = directory + "/in";
    if(mkfifo(pipe_name.c_str(), 0666) != 0) 
        cout << "failed to make pipe for system " << id << endl;
    this->input_pipe = open(pipe_name.c_str(), O_RDONLY | O_NONBLOCK);
}

void System::run(int read_fd_pipe) {
    fd_set inputs;
    int max_fd = 0;
    int ready = 0;
    while (1) {
        FD_ZERO(&inputs);
        FD_SET(read_fd_pipe, &inputs);
        max_fd = read_fd_pipe;
        FD_SET(input_pipe, &inputs);
        max_fd = input_pipe ? input_pipe > read_fd_pipe : max_fd;
        ready = select(max_fd+1, &inputs, NULL, NULL, NULL);

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
    cout << "from system: " << massage << endl;
}

void System::handleInputFrame(int input_pipe) {
    
}