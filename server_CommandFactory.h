#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include "server_Command.h"
#include "server_LogInfo.h"
#include "server_ProtectedFS.h"
#include "server_ProtectedResponses.h"
#include <string.h>

class CommandFactory {
  private:
    ProtectedFS* fs;
    ProtectedResponses* responses;
    LogInfo logger;
    bool* dead;

  public:
    CommandFactory(ProtectedFS* fs, ProtectedResponses* responses, bool* dead);
    Command* create(std::string str);
};

#endif
