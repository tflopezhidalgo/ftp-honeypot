#ifndef SERVER_COMMANDS_H
#define SERVER_COMMANDS_H

#include "server_Command.h"
#include "server_LogInfo.h"
#include "server_ProtectedFS.h"
#include "server_ProtectedResponses.h"

class UserCommand : public Command {
  public:
    UserCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l);
    std::string execute();
    ~UserCommand();
};

class PassCommand : public Command {
  public:
    PassCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l);
    std::string execute();
    ~PassCommand();
};

class SystCommand : public Command {
  public:
    SystCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l);
    std::string execute();
    ~SystCommand();
};

class ListCommand : public Command {
  public:
    ListCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l);
    std::string execute();
    ~ListCommand();
};

class HelpCommand : public Command {
  public:
    HelpCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l);
    std::string execute();
    ~HelpCommand();
};

class PWDCommand : public Command {
  public:
    PWDCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l);
    std::string execute();
    ~PWDCommand();
};

class MKDCommand : public Command {
  private:
    std::string dir;

  public:
    MKDCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l,
               std::string arg);
    std::string execute();
    ~MKDCommand();
};

class RMDCommand : public Command {
  private:
    std::string dir;

  public:
    RMDCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l,
               std::string arg);
    std::string execute();
    ~RMDCommand();
};

class InvalidCommand : public Command {
  public:
    InvalidCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l);
    std::string execute();
    ~InvalidCommand();
};

class QuitCommand : public Command {
  public:
    QuitCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l);
    std::string execute();
    ~QuitCommand();
};

#endif
