#ifndef PROTECTED_FS_H
#define PROTECTED_FS_H

#include <mutex>
#include <set>
#include <string.h>

class ProtectedFS {
  private:
    std::mutex mutex;
    std::set<std::string> files;

  public:
    ProtectedFS();
    std::set<std::string>* list();
    bool make(std::string dir);
    bool remove(std::string dir);
    ~ProtectedFS();
};

#endif
