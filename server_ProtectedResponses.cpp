#include "server_ProtectedResponses.h"
#include <string>
#include <fstream>

#define EQUAL_DEL '='

using namespace std;

ProtectedResponses::ProtectedResponses(std::string file_name){

    fstream in(file_name);
    string key, value;

    while(getline(in, key, EQUAL_DEL)){
        getline(in, value);
        responses.insert(pair<string,string>(key, value));
    }

    in.close();
}

string ProtectedResponses::getValue(string key){ 
    return this->responses[key]; 
}

ProtectedResponses::~ProtectedResponses(){


}
