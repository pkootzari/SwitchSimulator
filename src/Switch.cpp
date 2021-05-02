#include "Switch.hpp"

using namespace std;

Switch::Switch(int numOfPorts, int id) {
    this->id = id;
    this->numOfPorts = numOfPorts;
    this->directory = "Switch" + to_string(id);
    for(int i = 0; i < numOfPorts; i++) {
        this->ports_status.insert({ i, DISCONNECTED });
        this->port_pipe_towrite.insert( {i, 0} ); // there is nowhere to send data for each port
    }


    if(mkdir(directory.c_str(), 0777) == -1)
        cout << "Switch " << id << " can't make its directory!\n";
    
    for(int i = 0; i < numOfPorts; i++) {
        string pipe_name = directory + "/port" + to_string(i);
        if(mkfifo(pipe_name.c_str(), 0666) != 0)
            cout << "failed to make pipe for switch " << id << endl;
        this->port_input_pipes.push_back(open(pipe_name.c_str(), O_RDONLY | O_NONBLOCK));
    }
}

void Switch::run(int read_fd_pipe) {
    // testing pipes
    int highest = read_fd_pipe;
    FD_ZERO(&readFDs);
    FD_SET(read_fd_pipe, &readFDs);
    for(int i = 0; i < numOfPorts; i++){
        FD_SET(this->port_input_pipes[i], &readFDs);
        if(this->port_input_pipes[i] > highest)
            highest = this->port_input_pipes[i];
    }
    if(select(highest + 1, &readFDs, NULL, NULL, NULL) < 0){
        cout<<"select error"<<endl;
        exit(EXIT_FAILURE);
    }
    char massage[256];
    read(read_fd_pipe, massage, 256);
    cout << "from switch: " << massage << endl;
}
