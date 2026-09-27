#include "../server/server_Authenticator.h"
#include <string>
#include <iostream>

Authenticator::Authenticator(std::string user, std::string pass) {
    // Estos pueden ser tomados directamente.
    this->user = user;
    this->pass = pass;

    this->passOK = false;
    this->userOK = false;

    std::cout << "Using user: " << this->user << std::endl;
    std::cout << "Using pass: " << this->pass << std::endl;
}

// La autentication se hace en dos pasos, 
// primero el usuario y luego la contraseña. 

void Authenticator::checkUser(std::string user) {
    if (this->user == user) {
        userOK = true;

        std::cout << "User verified: " << this->user << std::endl;
    }
}

void Authenticator::checkPassword(std::string pass) {
    if (this->pass == pass) {
        passOK = true;

        std::cout << "Pass verified: " << this->pass << std::endl;
    }
}

bool Authenticator::logged() { return (userOK && passOK); }
