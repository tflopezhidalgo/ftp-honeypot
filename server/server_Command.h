#ifndef COMMAND_H
#define COMMAND_H

#include "../server/server_Authenticator.h"
#include "../server/server_ProtectedFS.h"
#include "../server/server_ConfigLoader.h"
#include <string>

class Command {
  protected:
    ProtectedFS* filesystem;
    ConfigLoader* config;
    Authenticator* authenticator;

  public:
    virtual std::string execute() = 0;
    virtual ~Command() {}
};

#endif
