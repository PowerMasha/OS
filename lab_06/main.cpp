#include <iostream>
#include "zmq.hpp"
#include <string>
#include <unistd.h>
#include <vector>
#include <csignal>
#include <set>
#include <algorithm>
#include "server.h"
#include "tree.h"

int main() {
    std::string command;
    IdTree ids;
    size_t child_pid = 0;
    int child_id = 0;
    zmq::context_t context(1);
    zmq::socket_t main_socket(context, ZMQ_REQ);
    int linger = 0;
    main_socket.setsockopt(ZMQ_SNDTIMEO, 2000);
    main_socket.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
    int port = bind_socket(main_socket);

    while (true) {
        std::cin >> command;
        if (command == "create") {
            size_t node_id;
            std::string result;
            std::cin >> node_id;
            if (child_pid == 0) {
                child_pid = fork();
                if (child_pid == -1) {
                    std::cout << "Unable to create first worker node\n";
                    child_pid = 0;
                    exit(1);
                } else if (child_pid == 0) {
                    create_node(node_id, port);
                } else {
                    child_id = node_id;
                    send_message(main_socket,"pid");
                    result = recieve_message(main_socket);

                }

            } else {

                std::ostringstream msg_stream;
                msg_stream << "create " << node_id;
                send_message(main_socket, msg_stream.str());
                result = recieve_message(main_socket);
            }

            if (result.substr(0,2) == "Ok") {
                ids.insert(node_id);
            }
            std::cout << result << "\n";

        } else if (command == "remove") {
            if (child_pid == 0) {
                std::cout << "Error:Not found\n";
                continue;
            }
            size_t node_id;
            std::cin >> node_id;
            if (node_id == child_id) {
                kill(child_pid, SIGTERM);
                kill(child_pid, SIGKILL);
                child_id = 0;
                child_pid = 0;
                std::cout << "Ok\n";
                ids.erase(node_id);
                continue;
            }
            std::string message_string = "remove " + std::to_string(node_id);
            send_message(main_socket, message_string);
            std::string recieved_message = recieve_message(main_socket);
            if (recieved_message.substr(0, std::min<int>(recieved_message.size(), 2)) == "Ok") {
                ids.erase(node_id);
            }
            std::cout << recieved_message << "\n";

        } else if (command == "exec") {
            int id, n;
            std::cin >> id >> n;
            std::vector<int> numbers(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> numbers[i];
            }

            std::string message_string = "exec " + std::to_string(id) + " " + std::to_string(n);
            for (int i = 0; i < n; ++i) {
                message_string += " " + std::to_string(numbers[i]);
            }

            send_message(main_socket, message_string);
            std::string recieved_message = recieve_message(main_socket);
            std::cout << recieved_message << "\n";

        } else if (command == "pingall") {
            send_message(main_socket,"pingall");
            std::string recieved = recieve_message(main_socket);
            std::istringstream is;
            if (recieved.substr(0,std::min<int>(recieved.size(), 5)) == "Error") {
                is = std::istringstream("");
            } else {
                is = std::istringstream(recieved);
            }

            std::set<int> received_ids;
            int rec_id;
            while (is >> rec_id) {
                received_ids.insert(rec_id);
            }
            std::vector from_tree = ids.get_nodes();
            std::cout << "Received: ";
            for (int i : received_ids) {
                std::cout<< i << " ";
            }
            std::cout << "\nAll nodes: ";
            for (int i : from_tree) {
                std::cout << i << " ";
            }
            std::cout << "\n";

        } else if (command == "exit") {
            break;
        }

    }

    return 0;
}
