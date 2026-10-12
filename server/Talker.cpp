#include "../server/Talker.h"
#include "../server/Command.h"
#include "../server/CommandFactory.h"
#include <iostream>
#include <string>

#define NEW_CLIENT_KEY "newClient"


std::string buildWelcomeMessage(ConfigLoader* r) {
    return "220 " + r->get(NEW_CLIENT_KEY);
}

Talker::Talker(int skt, ProtectedFS* filesystem, ConfigLoader* config)
    : skt(skt), factory(filesystem, config, &dead) {
    this->config = config;
    this->filesystem = filesystem;
    this->dead = false;
}

void Talker::run() {
    skt.send(buildWelcomeMessage(this->config));

    std::cout << "- Se conectó nuevo cliente -" << std::endl;
    std::string cmd_str;

    // EN la ultima iteracion se queda trabado en el receiveMsg
    while (skt.receive(cmd_str) && !dead) {

        std::cout << "Se recibio: " << cmd_str;

        Command* cmd = this->factory.create(cmd_str);
        skt.send(cmd->execute());
        delete cmd;
        cmd_str.clear();

        std::cout << "se llama a receive - \n";
    }
    std::cout << " - Se borro un cliente - \n";
    this->dead = true;
}

void Talker::stop() {
    this->skt.kill();
    this->dead = true;
}

bool Talker::is_dead() { return this->dead; }

Talker::~Talker() {}
