#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include "server_Command.h"
#include <string.h>
#include "server_ProtectedFS.h"
#include "server_ProtectedResponses.h"
#include "server_LogInfo.h"

class CommandFactory{
    private:
        ProtectedFS* fs;
        ProtectedResponses* responses;
        LogInfo logger;
        bool *dead;

    public:
        CommandFactory(ProtectedFS* fs, 
                       ProtectedResponses* responses,
                       bool* dead);
        Command* createCommand(std::string str);
};

#endif
