#ifndef SERVER_TALKER_H
#define SERVER_TALKER_H

#include "common_Socket.h"
#include "server_CommandFactory.h"
#include "server_Thread.h"

class Talker : public Thread {
  private:
    bool dead;
    Socket skt;
    CommandFactory factory;
    ProtectedFS* filesystem;
    ConfigLoader* responses;

  public:
    Talker(int skt, ProtectedFS* filesystem, ConfigLoader* responses);
    void run();
    void stop();
    bool is_dead();
    ~Talker();
};

#endif
