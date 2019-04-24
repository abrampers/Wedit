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

class MainWindow;

const int MAX_PENDING = 10;

const std::string SERVER_HOST = "0.0.0.0";
const int SERVER_PORT = 5000;

class Peer {
private:
    int port_number;
    int server_socket_ID;
    std::vector<int> client_sock_IDs;
    fd_set readfds;
    int max_sd;
    std::thread server_thread;
    MainWindow *w;

    void accept();
    void leave();

public:
    CRDT crdt;

    Peer(int port_number, MainWindow *w);
    ~Peer();

    int Connect(std::string host, int port);
    void Send(std::string payload) const;

    std::vector<std::pair<std::string, int> > GetConnectedIP();
    void Test();
};

#endif
