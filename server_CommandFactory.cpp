#include "server_CommandFactory.h"
#include "server_Commands.h"
#include "server_Command.h"
#include <sstream>
#include <string>
#include <iostream>

#define USER_CMD "USER"
#define PASS_CMD "PASS"
#define SYST_CMD "SYST"
#define LIST_CMD "LIST"
#define HELP_CMD "HELP"
#define PWD_CMD "PWD"
#define MKD_CMD "MKD"
#define RMD_CMD "RMD"
#define QUIT_CMD "QUIT"
#define SPACE_DEL ' '

CommandFactory::CommandFactory(ProtectedFS* fs,  
                               ProtectedResponses* responses,
                               bool* dead) : 
                               logger(responses->getValue("user"), 
                               responses->getValue("password")){
    this->fs = fs;
    this->responses = responses;
    this->dead = dead;
}

Command* CommandFactory::createCommand(std::string str){
    std::string cmd, arg;
    std::istringstream split(str);

    std::getline(split, cmd, SPACE_DEL);
    std::getline(split, arg);

    if (cmd.back() == '\n')
        cmd.pop_back();

    if(arg.back() == '\n')
        arg.pop_back();

    if (cmd == USER_CMD){
        this->logger.tryUser(arg);
        return new UserCommand(fs, responses, &logger);
    }else if (cmd == PASS_CMD){
        this->logger.tryPass(arg);
        return new PassCommand(fs, responses, &logger);
    }else if (cmd == SYST_CMD)
        return new SystCommand(fs, responses, &logger);
    else if (cmd == LIST_CMD)
        return new ListCommand(fs, responses, &logger);
    else if (cmd == HELP_CMD)
        return new HelpCommand(fs, responses, &logger);
    else if (cmd == PWD_CMD)
        return new PWDCommand(fs, responses, &logger);
    else if (cmd == MKD_CMD)
        return new MKDCommand(fs, responses, &logger, arg);
    else if (cmd == RMD_CMD)
        return new RMDCommand(fs, responses, &logger, arg);
    else if (cmd ==QUIT_CMD){
        *dead = true;
        return new QuitCommand(fs, responses, &logger);
    }else{
        return new InvalidCommand(fs, responses, &logger);
    }

}

