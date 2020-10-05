#include <zmq.h>
#include <iostream>
#include "lib.h"


int main() {
    ReqSocket main_socket;
    main_socket.Attach(4020);
    PubSocket counter_socket;
    counter_socket.Attach(4021);
    std::string input;
    while (std::getline(std::cin, input)) {
        main_socket.SendMessage(input, false);
        counter_socket.SendMessage(std::to_string(input.size()),true);
        std::cout << main_socket.ReceiveMessage() << "\n";
    }


    return 0;
}