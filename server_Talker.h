#ifndef SERVER_TALKER_H
#define SERVER_TALKER_H

#include "server_CommandFactory.h"
#include "server_Thread.h"
#include "common_Socket.h"

class Talker: public Thread{
    private:
        bool dead;
        Socket skt;
        CommandFactory factory;
        ProtectedFS* filesystem;
        ProtectedResponses* responses;

    public:
        Talker(int skt, 
               ProtectedFS* filesystem,
               ProtectedResponses* responses);
        void run();
        void stop();
        bool is_dead();
        ~Talker();
};

#endif
