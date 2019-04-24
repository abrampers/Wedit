#include "Peer.hpp"
#include <iostream>
#include <thread>

int main() {

    Peer p(8000);
    // std::thread sendThread(sendMessage, p);
    p.getConnectedIP();
    
    
    // sendThread.join();
    // listenThread.join();

    return 0;
}