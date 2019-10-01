#include "server_AcceptorSocket.h"
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>

AcceptorSocket::AcceptorSocket(std::string service){
    struct addrinfo h;
    struct addrinfo *ptr = NULL;

    memset(&h, 0, sizeof(struct addrinfo));
    h.ai_family = AF_INET;
    h.ai_socktype = SOCK_STREAM;
    h.ai_flags = AI_PASSIVE;
    
    getaddrinfo(NULL, service.c_str(), &h, &ptr);

    this->skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    //Chequear errores
    bind(this->skt, ptr->ai_addr, ptr->ai_addrlen);
    freeaddrinfo(ptr);
    listen(this->skt, 20);
}

int AcceptorSocket::acceptSocket(){
    return accept(this->skt, NULL, NULL);
}

void AcceptorSocket::kill(){
    shutdown(this->skt, SHUT_RDWR);
    close(this->skt);
}

AcceptorSocket::~AcceptorSocket() { }
