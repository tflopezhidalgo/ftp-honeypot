#include "server_ClientManager.h"
#include "server_AcceptorSocket.h"
#include "server_ProtectedResponses.h"
#include "server_ProtectedFS.h"
#include <string>
#include <iostream>

ClientManager::ClientManager(std::string service, std::string config) : 
                             acceptor(service), responses(config) { }

void ClientManager::run(){
    this->alive = true; 
    int new_skt = -1;
    while ((new_skt = this->acceptor.acceptSocket()) != -1 && alive){
        Talker* talker = new Talker(new_skt, &filesystem, &responses);
        talker->start();
        talkers.push_back(talker);    

        auto it = talkers.begin();
        while (it != talkers.end()){
            if ((*it)->is_dead()){
                std::cout << "Se cierra socket muerto\n";
                (*it)->stop();
                (*it)->join();
                delete (*it);
                it = talkers.erase(it);
                std::cout << "Cantidad de talkers " << talkers.size() << '\n';
             }else{
                ++it; 
             }
        }
    }
    for (Talker* talker : talkers){
        if(talker){
            std::cout << "Se mata socket\n";
           talker->stop();
            talker->join();
            delete talker;
        }
    }      
}

void ClientManager::kill(){
   this->acceptor.kill();
   this->alive = false;
}

ClientManager::~ClientManager() {  }
