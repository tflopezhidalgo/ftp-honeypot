#include <iostream>
#include "common_Socket.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]){

    Socket skt(argv[1], argv[2]);
    bool exit_set = false;
    std::string buffer;
   
    skt.receiveMsg(buffer);
    std::cout << buffer;
    buffer.clear();

    while (!exit_set){
        if(!getline(std::cin, buffer))
            break;
        if (buffer == "QUIT")
            exit_set = true;
        if (skt.sendMsg(buffer + '\n') == 0)
            break;
        buffer.clear();
        if (skt.receiveMsg(buffer) == 0)
            break;
        if (buffer.find("150") != std::string::npos){
            std::string buf2;
            while (buffer.find("226") == std::string::npos){
                skt.receiveMsg(buf2);
                buffer += buf2;
                buf2.clear();
            }
        }
        std::cout << buffer;
    }

    skt.kill();
    
    return 0;
}
