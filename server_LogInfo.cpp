#include "server_LogInfo.h"
#include <string>

LogInfo::LogInfo(std::string user, std::string pass){
    this->user = user;
    this->pass = pass;
    passOK = false;
    userOK = false;
}

void LogInfo::tryUser(std::string user){
    if (this->user == user){
        userOK = true;
        passOK = false;
    }
}

void LogInfo::tryPass(std::string pass){
    if (this->pass == pass)
        passOK = true;

}

bool LogInfo::logged(){
    return (userOK && passOK);
}

