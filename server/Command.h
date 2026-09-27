#ifndef COMMAND_H
#define COMMAND_H

#include "../server/Authenticator.h"
#include "../server/ProtectedFS.h"
#include "../server/ConfigLoader.h"
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
