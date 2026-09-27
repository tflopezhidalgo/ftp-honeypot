#ifndef PROTECTEDRESP_H
#define PROTECTEDRESP_H

#include <map>
#include <mutex>
#include <string>

class ProtectedResponses {
  private:
    std::map<std::string, std::string> responses;

  public:
    ProtectedResponses(std::string file_name);
    std::string get(std::string k);
    void set(std::string k, std::string v);
    ~ProtectedResponses();
};

#endif
