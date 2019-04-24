#include "Peer.hpp"
#include <iostream>
#include <thread>

int main() {
    std::string huyu;

    Peer p(5000);
    // std::thread sendThread(sendMessage, p);
    p.getConnectedIP();
    
    // sendThread.join();
    // listenThread.join();

    return 0;
}