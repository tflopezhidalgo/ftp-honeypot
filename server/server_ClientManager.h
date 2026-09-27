#ifndef client_MANAGER_H
#define client_MANAGER_H

#include "../server/server_AcceptorSocket.h"
#include "../server/server_ProtectedFS.h"
#include "../server/server_ConfigLoader.h"
#include "../server/server_Talker.h"
#include "../server/server_Thread.h"
#include <string>
#include <vector>

class ClientManager : public Thread {
  private:
    AcceptorSocket acceptor;
    std::vector<Talker*> talkers;
    ProtectedFS filesystem;
    ConfigLoader config;
    bool alive;

    void dropStaleConnections();

  public:
    ClientManager(std::string service, std::string config);
    void run();
    void kill();
    ~ClientManager();
};

#endif
