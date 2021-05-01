#include "Switch.hpp"

using namespace std;

Switch::Switch(int numOfPorts, int id) {
    this->id = id;
    this->numOfPorts = numOfPorts;

    string directory = "Switch" + to_string(id);
    if(mkdir(directory.c_str(), 0777) == -1)
        cout << "Switch " << id << "can't make its directory!\n";

    string read_dirpipe = directory+"/read";
    string write_dirpipe = directory+"/write";
    if(mkfifo(read_dirpipe.c_str(), 0666) != 0)
        cout << "faild to make pipe for switch " << id << endl;
    if(mkfifo(write_dirpipe.c_str(), 0666) != 0)
        cout << "faild to make pipe for switch " << id << endl;
    read_pipe = open(read_dirpipe.c_str(), O_RDONLY | O_NONBLOCK);
    write_pipe = open(write_dirpipe.c_str(), O_WRONLY | O_NONBLOCK);
}