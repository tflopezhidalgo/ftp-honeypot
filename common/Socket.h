#ifndef SOCKET_H
#define SOCKET_H

#include <cstring>
#include <string>

class Socket {
  private:
    int fd;

  public:
    Socket(int open_fd);
    Socket(std::string host, std::string service);
    int send(std::string msg);
    int receive(std::string& msg);
    void kill();
    ~Socket();
};

#endif
