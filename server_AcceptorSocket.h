#ifndef ACCEPTOR_SOCKET_H
#define ACCEPTOR_SOCKET_H

#include <string>

class AcceptorSocket{
    private:
        int skt;

    public:
        AcceptorSocket(std::string service);
        int acceptSocket(); 
        void kill();
        ~AcceptorSocket();
};

#endif
