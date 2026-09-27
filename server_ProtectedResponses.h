#ifndef PROTECTEDRESP_H
#define PROTECTEDRESP_H

#include <map>
#include <mutex>
#include <string>

class ProtectedResponses {
  private:
    std::map<std::string, std::string> responses;
    std::mutex m;

  public:
    ProtectedResponses(std::string file_name);
    std::string getValue(std::string key);
    ~ProtectedResponses();
};

#endif
