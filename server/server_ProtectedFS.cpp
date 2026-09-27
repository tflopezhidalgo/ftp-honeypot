#include "../server/server_ProtectedFS.h"
#include <mutex>
#include <set>
#include <string>

// TODO: Chequear todas las exceptions acá

ProtectedFS::ProtectedFS() {}

std::set<std::string>* ProtectedFS::list() {
    std::unique_lock<std::mutex> lck(this->mutex);
    return &this->files;
}

bool ProtectedFS::make(std::string dir) {
    std::unique_lock<std::mutex> lck(this->mutex);
    bool fExists = !!this->files.count(dir);

    if (!fExists) {
        this->files.insert(dir);
        return 0;
    }
    return 1;
}

bool ProtectedFS::remove(std::string dir) {
    std::unique_lock<std::mutex> lck(this->mutex);
    bool fExists = !!this->files.count(dir);

    if (fExists) {
        this->files.erase(this->files.find(dir));
        return 0;
    }
    return 1;
}

ProtectedFS::~ProtectedFS() {}
