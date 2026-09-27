#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include "server_Command.h"
#include "server_LogInfo.h"
#include "server_ProtectedFS.h"
#include "server_Responses.h"
#include <string.h>

class CommandFactory {
  private:
    ProtectedFS* fs;
    Responses* responses;
    LogInfo logger;
    bool* dead;

  public:
    CommandFactory(ProtectedFS* fs, Responses* responses, bool* dead);
    Command* create(std::string str);
};

#endif
