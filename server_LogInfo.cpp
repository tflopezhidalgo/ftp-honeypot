#include "server_LogInfo.h"
#include <string>
#include <iostream>

LogInfo::LogInfo(std::string user, std::string pass) {
    this->user = user;
    this->pass = pass;
    passOK = false;
    userOK = false;

    std::cout << "Using user: " << this->user << std::endl;
    std::cout << "Using pass: " << this->pass << std::endl;
}

void LogInfo::tryUser(std::string user) {
    if (this->user == user) {
        userOK = true;
        passOK = false;

        std::cout << "User verified: " << this->user << std::endl;
    }
}

void LogInfo::tryPass(std::string pass) {
    if (this->pass == pass) {
        passOK = true;

        std::cout << "Pass verified: " << this->pass << std::endl;
    }
}

bool LogInfo::logged() { return (userOK && passOK); }
