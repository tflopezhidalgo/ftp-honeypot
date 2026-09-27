#ifndef PROTECTEDRESP_H
#define PROTECTEDRESP_H

#include <map>
#include <mutex>
#include <string>

class Responses {
  private:
    std::map<std::string, std::string> responses;

  public:
    Responses(std::string filename);
    std::string get(std::string k);
    void set(std::string k, std::string v);
    ~Responses();
};

#endif
