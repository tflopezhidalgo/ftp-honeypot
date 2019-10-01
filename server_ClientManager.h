#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "server_Thread.h"
#include "server_ProtectedFS.h"
#include "server_ProtectedResponses.h"
#include "server_AcceptorSocket.h"
#include "server_Talker.h"
#include <vector>
#include <string>

class ClientManager: public Thread{
    private:
        AcceptorSocket acceptor;
        std::vector<Talker*> talkers;
        ProtectedFS filesystem;
        ProtectedResponses responses;
        bool alive;

    public:
        ClientManager(std::string service, 
                      std::string config);
        void run();
        void kill();
        ~ClientManager();
};

#endif
