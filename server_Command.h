#ifndef COMMAND_H
#define COMMAND_H

#include "server_LogInfo.h"
#include "server_ProtectedFS.h"
#include "server_Responses.h"
#include <string>

class Command {
  protected:
    ProtectedFS* filesystem;
    Responses* responses;
    LogInfo* logger;

  public:
    virtual std::string execute() = 0;
    virtual ~Command() {}
};

#endif
