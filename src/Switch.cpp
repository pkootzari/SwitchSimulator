#include "Switch.hpp"

using namespace std;

Switch::Switch(int numOfPorts, int id) {
    this->MASSAGE_SIZE = 128;
    this->id = id;
    this->numOfPorts = numOfPorts;
    this->directory = "switch" + to_string(id);
    for(int i = 0; i < numOfPorts; i++) {
        this->ports_status.insert({ i, DISCONNECTED });
        this->port_pipe_towrite.insert( {i, 0} ); // there is nowhere to send data for each port
    }
}

int Switch::getID() { return id; }

int Switch::getNumOfPorts() { return numOfPorts; }

void Switch::initiatePipes() {
    if(mkdir(directory.c_str(), 0777) == -1)
        cout << "Switch " << id << " can't make its directory!\n";
    
    for(int i = 0; i < numOfPorts; i++) {
        string pipe_name = directory + "/port" + to_string(i);
        if(mkfifo(pipe_name.c_str(), 0666) != 0)
            cout << "failed to make pipe for switch " << id << endl;
        int temp;
        if ((temp = open(pipe_name.c_str(), O_RDONLY | O_NONBLOCK)) < 0)
            cout << "faild to open the pipe for switch " << id << endl; 
        cout << "switch " << id << " opened: " << temp << endl;
        this->port_input_pipes.push_back(temp);
    }
}

void Switch::run(int read_fd_pipe) {
    initiatePipes();
    
    fd_set inputs;
    int max_fd = 0;
    while (1) {
        FD_ZERO(&inputs);
        FD_SET(read_fd_pipe, &inputs);
        for(int i = 0; i < numOfPorts; i++){
            FD_SET(this->port_input_pipes[i], &inputs);
            if(this->port_input_pipes[i] > max_fd)
                max_fd = this->port_input_pipes[i];
        }
        if(select(1000, &inputs, NULL, NULL, NULL) < 0)
            cout<<"select error in switch " << id <<endl;

        if(FD_ISSET(read_fd_pipe, &inputs)) {
            handleManagerCommand(read_fd_pipe);
        } else {
            for(int i = 0; i < numOfPorts; i++) {
                if(FD_ISSET(this->port_input_pipes[i], &inputs)) {
                    handleInputFrame(i, this->port_input_pipes[i]);
                }
            }
        }
    }
}

void Switch::handleManagerCommand(int read_fd_pipe) {
    char massage[MASSAGE_SIZE];
    read(read_fd_pipe, massage, MASSAGE_SIZE);
    cout << "for switch " << id << " : " << massage << endl;
}

void Switch::handleInputFrame(int port_num, int pipe_fd) {
    char massage[MASSAGE_SIZE];
    read(pipe_fd, massage, MASSAGE_SIZE);
    cout << "incoming frame for system " << id << " : " << massage << endl;
}
