#include<zmq.h>
#include <iostream>
#include "lib.h"

int main() {
    RepSocket main_socket;
    main_socket.Attach(4020);
    PubSocket counter_socket;
    counter_socket.Attach(4022);
    while (true) {
        std::string recieved_message = main_socket.ReceiveMessage();
        std::cout << recieved_message << '\n';
        counter_socket.SendMessage(std::to_string(recieved_message.size()),true);
        main_socket.SendMessage("OK", false);
    }
    return 0;
};