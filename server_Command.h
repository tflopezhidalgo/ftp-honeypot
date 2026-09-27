#ifndef COMMAND_H
#define COMMAND_H

#include "server_Authenticator.h"
#include "server_ProtectedFS.h"
#include "server_ConfigLoader.h"
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
