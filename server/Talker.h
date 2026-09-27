#ifndef TALKER_H
#define TALKER_H

#include "../common/Socket.h"
#include "../server/CommandFactory.h"
#include "../server/Thread.h"

// Conexion 1 a 1 con un cliente.

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
