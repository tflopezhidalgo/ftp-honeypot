#ifndef client_MANAGER_H
#define client_MANAGER_H

#include "../server/AcceptorSocket.h"
#include "../server/ProtectedFS.h"
#include "../server/ConfigLoader.h"
#include "../server/Talker.h"
#include "../server/Thread.h"
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
