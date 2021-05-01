#include "System.hpp"

using namespace std;

System::System(int id) {
    this->id = id;
    if(mkdir(("System" + to_string(id)).c_str(), 0777) == -1)
        cout << "System " << id << "can't make its directory!\n"; 

}