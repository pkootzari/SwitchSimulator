#include "Switch.hpp"

using namespace std;

Switch::Switch(int numOfPorts, int id) {
    this->id = id;
    this->numOfPorts = numOfPorts;
    this->directory = "Switch" + to_string(id);
    for(int i = 0; i < numOfPorts; i++)
        this->ports_status.insert({ i, DISCONNECTED });

    if(mkdir(directory.c_str(), 0777) == -1)
        cout << "Switch " << id << "can't make its directory!\n";

    for(int i = 0; i < numOfPorts; i++) {
        string pipe_name = directory + "/port" + to_string(i);
        if(mkfifo(pipe_name.c_str(), 0666) != 0)
            cout << "failed to make pipe for switch " << id << endl;
        this->port_pipes.push_back(open(pipe_name.c_str(), O_RDONLY | O_NONBLOCK));
    }
}

void Switch::run(int read_fd_pipe) {

}
