#include "server_Commands.h"
#include "server_ProtectedFS.h"
#include "server_ProtectedResponses.h"
#include <set>

#define PASS_REQUIRED_KEY "passRequired"
#define UNKNOWN_COMMAND_KEY "unknownCommand"
#define COMMANDS_KEY "commands"
#define PWD_SUCCESS_KEY "pwdSuccess"

// LOGIN
#define LOGIN_SUCCESS_KEY "loginSuccess"
#define LOGIN_FAILED_KEY "loginFailed"

#define SYSTEM_INFO_KEY "systemInfo"
#define CLIENT_NOT_LOGGED_KEY "clientNotLogged"

// LIST
#define LIST_BEGIN_KEY "listBegin"
#define LIST_END_KEY "listEnd"

// MKDIR
#define MKD_FAILED_KEY "mkdFailed"
#define MKD_SUCCESS_KEY "mkdSuccess"

// RMDIR
#define RMD_FAILED_KEY "rmdFailed"
#define RMD_SUCCESS_KEY "rmdSuccess"

// QUIT
#define QUIT_SUCCESS_KEY "quitSuccess"

std::string buildLoginRequiredMessage(ProtectedResponses* r) {
    return "530 " + r->get(CLIENT_NOT_LOGGED_KEY) + '\n';
}

std::string buildUnknownCommandMessage(ProtectedResponses* r) {
    return "530 " + r->get(UNKNOWN_COMMAND_KEY) + '\n';
}

std::string buildLoginSuccessMessage(ProtectedResponses* r) {
    return "230 " + r->get(LOGIN_SUCCESS_KEY) + '\n';
}

std::string buildLoginFailedMessage(ProtectedResponses* r) {
    return "530 " + r->get(LOGIN_FAILED_KEY) + '\n';
}

UserCommand::UserCommand(ProtectedFS* fs, ProtectedResponses* responses,
                         LogInfo* logger) {
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string UserCommand::execute() {
    return ("331 " + this->responses->get(PASS_REQUIRED_KEY) + '\n');
}

UserCommand::~UserCommand() {}

PassCommand::PassCommand(ProtectedFS* fs, ProtectedResponses* responses,
                         LogInfo* logger) {
    this->filesystem = fs;
    this->responses = responses;
    this->logger = logger;
}

std::string PassCommand::execute() {
    return logger->logged() ? buildLoginSuccessMessage(this->responses)
                            : buildLoginFailedMessage(this->responses);
}

PassCommand::~PassCommand() {}

SystCommand::SystCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l) {
    this->filesystem = f;
    this->responses = r;
    this->logger = l;
}

std::string SystCommand::execute() {
    if (logger->logged())
        return "215 " + this->responses->get(SYSTEM_INFO_KEY) + '\n';
    else
        return buildLoginRequiredMessage(this->responses);
}

SystCommand::~SystCommand() {}

ListCommand::ListCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l) {
    this->filesystem = f;
    this->responses = r;
    this->logger = l;
}

std::string ListCommand::execute() {
    if (!logger->logged())
        return buildLoginRequiredMessage(this->responses);

    std::string msg("150 " + this->responses->get(LIST_BEGIN_KEY) + '\n');

    std::set<std::string>* buffer = this->filesystem->listFiles();

    for (auto str : *buffer)
        msg = msg + "drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34 " + str + '\n';

    return msg + "226 " + this->responses->get(LIST_END_KEY) + '\n';
}

ListCommand::~ListCommand() {}

HelpCommand::HelpCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l) {
    this->filesystem = f;
    this->responses = r;
    this->logger = l;
}

std::string HelpCommand::execute() {
    if (!logger->logged())
        return buildLoginRequiredMessage(this->responses);

    return "214 " + this->responses->get(COMMANDS_KEY) + '\n';
}

HelpCommand::~HelpCommand() {}

PWDCommand::PWDCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l) {
    this->filesystem = f;
    this->responses = r;
    this->logger = l;
}

std::string PWDCommand::execute() {
    if (logger->logged())
        return "257 " + this->responses->get(PWD_SUCCESS_KEY) + '\n';

    return buildLoginRequiredMessage(this->responses);
}

PWDCommand::~PWDCommand() {}

MKDCommand::MKDCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l,
                       std::string d) {
    this->dir = d;
    this->filesystem = f;
    this->responses = r;
    this->logger = l;
}

std::string MKDCommand::execute() {
    if (!logger->logged())
        return buildLoginRequiredMessage(this->responses);

    if (this->filesystem->makeDir(this->dir))
        return "550 " + this->responses->get(MKD_FAILED_KEY) + '\n';

    return "257 \"" + this->dir + "\" " +
           this->responses->get(MKD_SUCCESS_KEY) + '\n';
}

MKDCommand::~MKDCommand() {}

RMDCommand::RMDCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l,
                       std::string d) {
    this->dir = d;
    this->filesystem = f;
    this->responses = r;
    this->logger = l;
}

std::string RMDCommand::execute() {
    if (!logger->logged())
        return buildLoginRequiredMessage(this->responses);

    if (this->filesystem->removeDir(this->dir))
        return "550 " + this->responses->get(RMD_FAILED_KEY) + '\n';

    return "250 \"" + this->dir + "\" " +
           this->responses->get(RMD_SUCCESS_KEY) + '\n';
}

RMDCommand::~RMDCommand() {}

InvalidCommand::InvalidCommand(ProtectedFS* f, ProtectedResponses* r,
                               LogInfo* l) {
    this->filesystem = f;
    this->responses = r;
    this->logger = l;
}

std::string InvalidCommand::execute() {
    return buildUnknownCommandMessage(this->responses);
}

InvalidCommand::~InvalidCommand() {}

QuitCommand::QuitCommand(ProtectedFS* f, ProtectedResponses* r, LogInfo* l) {
    this->filesystem = f;
    this->responses = r;
    this->logger = l;
}

std::string QuitCommand::execute() {
    return "221 " + this->responses->get(QUIT_SUCCESS_KEY) + '\n';
}

QuitCommand::~QuitCommand() {}
