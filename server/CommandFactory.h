#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include "../server/Command.h"
#include "../server/Authenticator.h"
#include "../server/ProtectedFS.h"
#include "../server/ConfigLoader.h"
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
