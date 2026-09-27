#include "../server/CommandFactory.h"
#include "../server/Command.h"
#include "../server/Commands.h"
#include <sstream>
#include <string>

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

CommandFactory::CommandFactory(ProtectedFS* fs, ConfigLoader* config,
                               bool* dead)
    : authenticator(config->get("user"), config->get("password")) {
    this->fs = fs;
    this->config = config;
    this->dead = dead;
}

Command* CommandFactory::create(std::string str) {
    std::string cmd, arg;
    std::istringstream split(str);

    std::getline(split, cmd, SPACE_DEL);
    std::getline(split, arg);

    if (cmd.back() == '\n')
        cmd.pop_back();

    if (arg.back() == '\n')
        arg.pop_back();

    if (cmd == USER_CMD) {
        this->authenticator.checkUser(arg);
        return new UserCommand(fs, config, &authenticator);
    } else if (cmd == PASS_CMD) {
        this->authenticator.checkPassword(arg);
        return new PassCommand(fs, config, &authenticator);
    } else if (cmd == SYST_CMD)
        return new SystCommand(fs, config, &authenticator);
    else if (cmd == LIST_CMD)
        return new ListCommand(fs, config, &authenticator);
    else if (cmd == HELP_CMD)
        return new HelpCommand(fs, config, &authenticator);
    else if (cmd == PWD_CMD)
        return new PWDCommand(fs, config, &authenticator);
    else if (cmd == MKD_CMD)
        return new MKDCommand(fs, config, &authenticator, arg);
    else if (cmd == RMD_CMD)
        return new RMDCommand(fs, config, &authenticator, arg);
    else if (cmd == QUIT_CMD) {
        *dead = true;
        return new QuitCommand(fs, config, &authenticator);
    } else {
        return new InvalidCommand(fs, config, &authenticator);
    }
}
