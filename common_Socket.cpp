#include "common_Socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <iostream>

// Ya me pasan el socket abierto (SocketManager)
Socket::Socket(int open_fd){
    this->fd = open_fd;
}

// Tengo que abrir el socket yo (soy cliente)
Socket::Socket(std::string host, std::string service){
    struct addrinfo h;
    struct addrinfo *r = NULL, *ptr = NULL;
    bool connected = false;

    memset(&h, 0, sizeof(struct addrinfo));
    h.ai_family = AF_INET;
    h.ai_socktype = SOCK_STREAM;
    h.ai_flags = 0;

    getaddrinfo(host.c_str(), service.c_str(), &h, &r);

    for (ptr = r; ptr != NULL && connected == false; ptr = ptr->ai_next){
        this->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (this->fd != -1){
            connect(this->fd, ptr->ai_addr, ptr->ai_addrlen);
            connected = true;
        }
    }

    freeaddrinfo(r);
}

int Socket::sendMsg(std::string msg){
    uint32_t total_sent = 0, sent = 0;
    char buf = 0;
    bool cont = true;
    while (total_sent < msg.size() && cont){
        buf = msg[total_sent];
        sent = send(fd, &buf, 1, MSG_NOSIGNAL);
        if (sent == 0)
            cont = false;
        total_sent += sent;
    }
    return total_sent;
}

int Socket::receiveMsg(std::string &msg){
   char buf = 0;
   bool cont = true;
   uint32_t total_received = 0, received = 0;
   while (buf != '\n' && cont){
       received = recv(this->fd, &buf, 1, 0);
       msg += buf;
       total_received += received;
       if (received == 0)
           cont = false;
    }   
    return total_received;
}

void Socket::kill(){
    shutdown(this->fd, SHUT_RDWR);
    close(this->fd);
}

Socket::~Socket(){

}

