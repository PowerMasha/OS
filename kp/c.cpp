#include<zmq.h>
#include <iostream>
#include "lib.h"
#include <thread>

void ListenToSocket(Socket& socket, char prog_symbol) {
    while (true) {
        std::string received = socket.ReceiveMessage();
        std::cout << (std::string(1, prog_symbol) + " processed " + received + " symbols\n");
    }
}

int main() {
    SubSocket a_counter;
    a_counter.Attach(4021);
    SubSocket b_counter;
    b_counter.Attach( 4022);

    std::thread t1(ListenToSocket, std::ref(a_counter), 'A');
    std::thread t2(ListenToSocket, std::ref(b_counter), 'B');

    t1.join();
    t2.join();
    return 0;
}