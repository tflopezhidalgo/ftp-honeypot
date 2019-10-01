#ifndef SERVER_COMMANDS_H
#define SERVER_COMMANDS_H

#include "server_ProtectedFS.h"
#include "server_ProtectedResponses.h"
#include "server_Command.h"
#include "server_LogInfo.h"

class UserCommand: public Command{
    public:
        UserCommand(ProtectedFS* fs,
                    ProtectedResponses* responses,
                    LogInfo* logger);
        std::string execute();
        ~UserCommand();
};

class PassCommand: public Command{
    public:
        PassCommand(ProtectedFS* fs,
                    ProtectedResponses* responses, 
                    LogInfo* logger);
        std::string execute();
        ~PassCommand();
};

class SystCommand: public Command{
    public:
        SystCommand(ProtectedFS* fs,
                    ProtectedResponses* responses,
                    LogInfo* logger);
        std::string execute();
        ~SystCommand();
};

class ListCommand: public Command{
    public:
        ListCommand(ProtectedFS* fs,
                    ProtectedResponses* responses,
                    LogInfo* logger);
        std::string execute();
        ~ListCommand();
};

class HelpCommand: public Command{
    public:
        HelpCommand(ProtectedFS* fs,
                    ProtectedResponses* responses,
                    LogInfo* logger);
        std::string execute();
        ~HelpCommand();
};

class PWDCommand: public Command{
    public:
        PWDCommand(ProtectedFS* fs,
                   ProtectedResponses* responses,
                   LogInfo* logger);
        std::string execute();
        ~PWDCommand();
};

class MKDCommand: public Command{
    private:
        std::string dir;
    public:
        MKDCommand(ProtectedFS* fs,
                   ProtectedResponses* responses,
                   LogInfo* logger,
                   std::string arg);
        std::string execute();
        ~MKDCommand();
};

class RMDCommand: public Command{
    private:
        std::string dir;
    public:
        RMDCommand(ProtectedFS* fs,
                   ProtectedResponses* responses,
                   LogInfo* logger,
                   std::string arg);
        std::string execute();
        ~RMDCommand();
};

class InvalidCommand: public Command{
    public:
        InvalidCommand(ProtectedFS* fs, 
                       ProtectedResponses* responses,
                       LogInfo* logger);
        std::string execute();
        ~InvalidCommand();

};

class QuitCommand: public Command{
    public:
        QuitCommand(ProtectedFS* fs,
                    ProtectedResponses* responses,
                    LogInfo* logger);
        std::string execute();
        ~QuitCommand();
};

#endif
