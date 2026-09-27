#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include "../server/server_Command.h"
#include "../server/server_Authenticator.h"
#include "../server/server_ProtectedFS.h"
#include "../server/server_ConfigLoader.h"
#include <string.h>

class CommandFactory {
  private:
    ProtectedFS* fs;
    ConfigLoader* config;
    Authenticator authenticator;
    bool* dead;

  public:
    CommandFactory(ProtectedFS* f, ConfigLoader* c, bool* dead);
    Command* create(std::string str);
};

#endif
