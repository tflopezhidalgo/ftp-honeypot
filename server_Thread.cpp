#include "server_Thread.h"
#include <thread>

Thread::Thread() {}

void Thread::start(){
    this->thread = std::thread(&Thread::run, this);
}

void Thread::join(){
    this->thread.join();
}

Thread::~Thread() {}
