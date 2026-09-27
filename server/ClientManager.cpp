#include "../server/ClientManager.h"
#include "../server/AcceptorSocket.h"
#include "../server/ConfigLoader.h"
#include <iostream>
#include <string>

ClientManager::ClientManager(std::string service, std::string config)
    : acceptor(service), config(config) {}

void ClientManager::dropStaleConnections() {
    auto it = this->talkers.begin();
    while (it != this->talkers.end()) {
        if ((*it)->is_dead()) {
            std::cout << "Se cierra socket muerto\n";
            (*it)->stop();
            (*it)->join();
            delete (*it);
            it = this->talkers.erase(it);
            std::cout << "Cantidad de talkers " << this->talkers.size()
                        << '\n';
        } else {
            ++it;
        }
    }
}

void ClientManager::run() {
    this->alive = true;

    int new_skt = -1;

    // Main loop.
    while ((new_skt = this->acceptor.acceptSocket()) != -1 && alive) {
        Talker* talker = new Talker(new_skt, &filesystem, &config);
        talker->start();
        this->talkers.push_back(talker);

        this->dropStaleConnections();
    }

    // Cerramos conexiones a medida que terminen.
    for (Talker* t : this->talkers) {
        if (t) {
            std::cout << "Se mata socket\n";
            t->stop();
            t->join();
            delete t;
        }
    }
}

void ClientManager::kill() {
    this->acceptor.kill();
    this->alive = false;
}

ClientManager::~ClientManager() {}
