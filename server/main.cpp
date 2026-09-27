#include "../server/ClientManager.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    ClientManager cm(argv[1], argv[2]);
    cm.start();

    std::string readed;

    while (readed != "q") {
        std::cin >> readed;
    }

    std::cout << "saliendo... \n";
    cm.kill();
    cm.join();

    return 0;
}
