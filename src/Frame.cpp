#include "../include/Frame.hpp"

using namespace std;

int Frame::max_sizeof_content = 50;

Frame::Frame(int from, int to, int type, string content) {
    this->from = from;
    this->to = to;
    this->type = type;
    this->content = content;
}

Frame::Frame(string massage) {
    vector<string> arguments = tokenizeInput(massage);
    if(arguments.size() < 4)
        cout << "Invalid frame type!\n";

    this->from      = stoi(arguments[0]);
    this->to        = stoi(arguments[1]);
    this->type      = stoi(arguments[2]);
    string in = arguments[3];
    string out = in.substr(0, in.find('#'));
    this->content   = out;
}

vector<string> Frame::splitString(string s) {
    vector<string> return_value;
    for (int i = 0; i < s.length(); i += Frame::max_sizeof_content) {
        string temp = s.substr(i, Frame::max_sizeof_content);
        return_value.push_back(temp); 
    }

    return return_value;
}

vector<Frame> Frame::makeFramesFromMsg(string msg, int from, int to) {
    vector<string> chunks = splitString(msg);
    vector<Frame> frames;
    for(int i = 0; i < chunks.size(); i++) {
        Frame f = Frame(from, to, FILE_C, chunks[i]);
        frames.push_back(f);
    }
    frames.push_back(Frame(from, to, FILE_E, ";"));
    return frames;
}

int Frame::getTo() { return this->to; }

int Frame::getFrom() { return this->from; }

int Frame::getType() { return this->type; }

string Frame::getContent() { return this->content; }

string Frame::toString() {
    string to = (this->to > 9) ? to_string(this->to) : "0"+to_string(this->to);
    string from = (this->from > 9) ? to_string(this->from) : "0"+to_string(this->from);
    string type = to_string(this->type);
    string c = content;
    while(c.length()!= Frame::max_sizeof_content)
        c += "#";

    return string(from + " " + to + " " + type + " " + c);
}

vector<string> Frame::tokenizeInput(string input) {
    stringstream inputStringStream(input);
    return vector<string>(istream_iterator<string>(inputStringStream),
                          istream_iterator<string>());
}


// int main(int argc, char const *argv[])
// {
//     ifstream ifs("Main.cpp");
//     string content( (std::istreambuf_iterator<char>(ifs) ),
//                        (std::istreambuf_iterator<char>()    ) );
//     ifs.close();

//     vector<Frame> f= Frame::makeFramesFromMsg(content, 1, 10);

//     ofstream msgf("msg.txt");
//     for(int i = 0; i < f.size(); i++)
//         msgf << f[i].getContent();
//     msgf.close();

//     ofstream logs("log.txt");
//     for(int i = 0; i < f.size(); i++)
//         logs << f[i].toString() << endl;
//     logs.close();

//     return 0;
// }
