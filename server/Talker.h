#ifndef TALKER_H
#define TALKER_H

#include "../common/Socket.h"
#include "../server/CommandFactory.h"
#include "../server/Thread.h"

// Representa una conexion con un cliente (1 a 1). Recibe y procesa
// los comandos enviados hasta que finaliza la conexion.

class Talker : public Thread {
  private:
    bool dead;
    Socket skt;
    CommandFactory factory;
    ProtectedFS* filesystem;
    ConfigLoader* config;

  public:
    Talker(int skt, ProtectedFS* filesystem, ConfigLoader* config);
    void run();
    void stop();
    bool is_dead();
    ~Talker();
};

#endif
