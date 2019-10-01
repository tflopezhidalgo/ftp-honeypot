#ifndef PROTECTED_FS_H
#define PROTECTED_FS_H

#include <mutex>
#include <string.h>
#include <set>

class ProtectedFS{
    private:
        std::mutex m;
        std::set<std::string> files;

    public:
        ProtectedFS();
        std::set<std::string>* listFiles();
        bool makeDir(std::string dir);
        bool removeDir(std::string dir);
        ~ProtectedFS();
};

#endif
