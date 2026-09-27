#include "../server/Talker.h"
#include "../server/Command.h"
#include "../server/CommandFactory.h"
#include <iostream>
#include <string>

Talker::Talker(int skt, ProtectedFS* filesystem, ConfigLoader* responses)
    : skt(skt), factory(filesystem, responses, &dead) {
    this->responses = responses;
    this->filesystem = filesystem;
    this->dead = false;
}

void Talker::run() {

    skt.sendMsg("220 " + this->responses->get("newClient") + '\n');
    std::cout << "- Se conectó nuevo cliente -" << std::endl;
    std::string cmd_str;

    // EN la ultima iteracion se queda trabado en el receiveMsg
    while (skt.receiveMsg(cmd_str) && !dead) {
        std::cout << "Se recibio: " << cmd_str;
        Command* cmd = this->factory.create(cmd_str);
        skt.sendMsg(cmd->execute());
        delete cmd;
        cmd_str.clear();
        std::cout << "se llama a receive\n";
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
