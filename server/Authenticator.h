#ifndef LOGINFO_H
#define LOGINFO_H

#include "../server/ProtectedFS.h"
#include "../server/ConfigLoader.h"
#include <string>

class Authenticator {
  private:
    bool passOK;
    bool userOK;
    std::string user;
    std::string pass;

  public:
    Authenticator(std::string user, std::string pass);
    void checkUser(std::string user);
    void checkPassword(std::string pass);
    bool logged();
};

#endif
