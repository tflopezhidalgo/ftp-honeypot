#include "server_ClientManager.h"
#include <string>
#include <iostream>

int main(int argc, char* argv[]){
    ClientManager cm(argv[1], argv[2]);
    cm.start();

    std::string readed;

    while(readed != "q"){
        std::cin >> readed;
    }

    std::cout << "saliendo... \n";
    cm.kill();
    cm.join();

    return 0;    
}
