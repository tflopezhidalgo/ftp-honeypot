#include "server_Commands.h"
#include "server_ProtectedFS.h"
#include "server_ProtectedResponses.h"
#include <iostream>
#include <set>

UserCommand::UserCommand(ProtectedFS* fs,
                         ProtectedResponses* responses,
                         LogInfo* logger){
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string UserCommand::execute(){
    return ("331 " + this->responses->getValue("passRequired") + '\n');
}

UserCommand::~UserCommand() {}

PassCommand::PassCommand(ProtectedFS* fs,
                         ProtectedResponses* responses,
                         LogInfo* logger){
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string PassCommand::execute(){
    if (logger->logged())
        return "230 " + this->responses->getValue("loginSuccess") + '\n';
    else
        return "530 " + this->responses->getValue("loginFailed") + '\n';
}

PassCommand::~PassCommand() {}

SystCommand::SystCommand(ProtectedFS* fs,
                         ProtectedResponses* responses,
                         LogInfo* logger){
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string SystCommand::execute(){
    if (logger->logged())
        return "215 " + this->responses->getValue("systemInfo") + '\n';
    else
        return "530 " + this->responses->getValue("clientNotLogged") + '\n';
}

SystCommand::~SystCommand() {}

ListCommand::ListCommand(ProtectedFS* fs,
                         ProtectedResponses* responses,
                         LogInfo* logger){
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string ListCommand::execute(){
    if (!logger->logged())
        return "530 " + this->responses->getValue("clientNotLogged") + '\n';

    std::string msg("150 " + this->responses->getValue("listBegin") + '\n'); 

    std::set<std::string> *buffer = this->filesystem->listFiles();
    
    for (auto str : *buffer)
        msg = msg + "drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34 " + str + '\n';

    return msg + "226 " + this->responses->getValue("listEnd") + '\n';
}

ListCommand::~ListCommand() {}

HelpCommand::HelpCommand(ProtectedFS* fs,
                         ProtectedResponses* responses,
                         LogInfo* logger){
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string HelpCommand::execute(){
    if (!logger->logged())
        return "530 " + this->responses->getValue("clientNotLogged") + '\n';

    return "214 " + this->responses->getValue("commands") + '\n';
}

HelpCommand::~HelpCommand() {}

PWDCommand::PWDCommand(ProtectedFS* fs,
                         ProtectedResponses* responses,
                         LogInfo* logger){
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string PWDCommand::execute(){
    if (logger->logged())
        return "257 " + this->responses->getValue("currentDirectoryMsg") + '\n';

    return "530 " + this->responses->getValue("clientNotLogged") + '\n'; 
}

PWDCommand::~PWDCommand() {}

MKDCommand::MKDCommand(ProtectedFS* fs,
                       ProtectedResponses* responses,
                       LogInfo* logger,
                       std::string arg){
    this->dir = arg;
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string MKDCommand::execute(){
    if (!logger->logged())
        return "530 " + this->responses->getValue("clientNotLogged") + '\n';
    
    if (this->filesystem->makeDir(this->dir))
        return "550 " + this->responses->getValue("mkdFailed") + '\n';    

    return "257 \"" + this->dir + "\" " + this->responses->getValue("mkdSuccess") + '\n';
}

MKDCommand::~MKDCommand() {}

RMDCommand::RMDCommand(ProtectedFS* fs,
                         ProtectedResponses* responses,
                         LogInfo* logger, 
                         std::string arg){
    this->dir = arg;
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string RMDCommand::execute(){
    if (!logger->logged())
        return "530 " + this->responses->getValue("clientNotLogged") + '\n';

    if (this->filesystem->removeDir(this->dir))
        return "550 " + this->responses->getValue("rmdFailed") + '\n';

    return  "250 \"" + this->dir + "\" " + this->responses->getValue("rmdSuccess") + '\n';
}

RMDCommand::~RMDCommand() {}


InvalidCommand::InvalidCommand(ProtectedFS* fs, 
                               ProtectedResponses* responses,
                               LogInfo* logger){
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string InvalidCommand::execute(){
    return "530 " + this->responses->getValue("unknownCommand") + '\n';
}

InvalidCommand::~InvalidCommand() {}


QuitCommand::QuitCommand(ProtectedFS* fs, 
                         ProtectedResponses* responses,
                         LogInfo* logger){
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string QuitCommand::execute(){
    return "221 " + this->responses->getValue("quitSuccess") + '\n';
}

QuitCommand::~QuitCommand() {}

