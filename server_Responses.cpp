#include "server_Responses.h"
#include <fstream>
#include <string>

#define EQUAL_DEL '='

using namespace std;

Responses::Responses(std::string filename) {

    fstream config_f(filename);
    string k, v;

    while (getline(config_f, k, EQUAL_DEL)) {
        getline(config_f, v);
        this->set(k, v);
    }

    config_f.close();
}

string Responses::get(string k) { 
    return this->responses[k]; 
}

void Responses::set(string k, string v) {
    this->responses[k] = v;
}

Responses::~Responses() {}
