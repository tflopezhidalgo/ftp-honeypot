#include "server_Talker.h"
#include "server_Command.h"
#include "server_CommandFactory.h"
#include <iostream>
#include <string>

Talker::Talker(int skt, ProtectedFS* filesystem, ProtectedResponses* responses)
    : skt(skt), factory(filesystem, responses, &dead) {
    this->responses = responses;
    this->filesystem = filesystem;
    this->dead = false;
}

void Talker::run() {

    skt.sendMsg("220 " + this->responses->get("newClient") + '\n');
    std::cout << "- Se conectó nuevo cliente -" << std::endl;
    std::string command;

    // EN la ultima iteracion se queda trabado en el receiveMsg
    while (skt.receiveMsg(command) && !dead) {
        std::cout << "Se recibio: " << command;
        Command* cmd = this->factory.create(command);
        skt.sendMsg(cmd->execute());
        delete cmd;
        command.clear();
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
