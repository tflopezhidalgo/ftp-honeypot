#include "server_ProtectedFS.h"
#include <set>
#include <string>
#include <mutex>
#include <iostream>

//TODO: Chequear todas las exceptions acá

ProtectedFS::ProtectedFS(){

}

std::set<std::string>* ProtectedFS::listFiles(){
    std::unique_lock<std::mutex> lck(m);
    return &this->files;
}

bool ProtectedFS::makeDir(std::string dir){
    std::unique_lock<std::mutex> lck(m);
    if (!this->files.count(dir)){
        this->files.insert(dir);
        return 0;
    }   
    return 1;
}

bool ProtectedFS::removeDir(std::string dir){
    std::unique_lock<std::mutex> lck(m);
    if (this->files.count(dir)){
        this->files.erase(files.find(dir));
        return 0;
    }
    return 1;
}

ProtectedFS::~ProtectedFS(){


}
