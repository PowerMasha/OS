#include <iostream>
#include <zmq.hpp>

int main(int argc, char** argv) {

    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    printf("Version %d.%d.%d\n", major, minor, patch);

}