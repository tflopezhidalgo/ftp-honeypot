#ifndef LOGINFO_H
#define LOGINFO_H

#include <string>
#include "server_ProtectedResponses.h"
#include "server_ProtectedFS.h"

class LogInfo{
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
