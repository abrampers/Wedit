#ifndef WEDIT_PEER_HPP_
#define WEDIT_PEER_HPP_

#include <vector>
#include <utility>
#include <string>
#include <thread>

#include <stdio.h>  
#include <string.h>   //strlen  
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>   //close  
#include <arpa/inet.h>    //close  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h>
#include <netdb.h> 

#include "crdt.h"

const int MAX_PENDING = 10;

const std::string SERVER_HOST = "0.0.0.0";
const int SERVER_PORT = 5000;

class Peer {
private:
    /* data */
    int portNumber;
    int serverSocketID;
    std::vector<int> clientSockIDs;
    fd_set readfds;
    int max_sd;
    std::thread serverThread;

    CRDT crdt;

    /* Method */
    void accept();
    void leave();

public:
    Peer(int portNumber);
    ~Peer();

    int connect(std::string host, int port);
    void send(std::string payload) const;

    std::vector<std::pair<std::string, int> > getConnectedIP();
    void test();
};

#endif
