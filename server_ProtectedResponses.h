#ifndef PROTECTEDRESP_H
#define PROTECTEDRESP_H

#include <map>
#include <string>
#include <mutex>

class ProtectedResponses{
    private:
        std::map<std::string, std::string> responses;
        std::mutex m;

    public:
        ProtectedResponses(std::string file_name);
        std::string getValue(std::string key);
        ~ProtectedResponses();
};

#endif
