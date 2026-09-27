#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "server_AcceptorSocket.h"
#include "server_ProtectedFS.h"
#include "server_Responses.h"
#include "server_Talker.h"
#include "server_Thread.h"
#include <string>
#include <vector>

class ClientManager : public Thread {
  private:
    AcceptorSocket acceptor;
    std::vector<Talker*> talkers;
    ProtectedFS filesystem;
    Responses responses;
    bool alive;

  public:
    ClientManager(std::string service, std::string config);
    void run();
    void kill();
    ~ClientManager();
};

#endif
