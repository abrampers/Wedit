#include "peer.h"
#include <iostream>
#include <thread>

int main() {

    Peer p(8000);
    p.GetConnectedIP();

    return 0;
}
