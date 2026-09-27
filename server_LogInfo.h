#ifndef LOGINFO_H
#define LOGINFO_H

#include "server_ProtectedFS.h"
#include "server_Responses.h"
#include <string>

class LogInfo {
  private:
    bool passOK;
    bool userOK;
    std::string user;
    std::string pass;

  public:
    LogInfo(std::string user, std::string pass);
    void tryUser(std::string user);
    void tryPass(std::string pass);
    bool logged();
};

#endif
