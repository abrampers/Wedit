#include "peer.h"
#include "mainwindow.h"
#include <iostream>

void error(const char *msg) {
    perror(msg);
    exit(0);
}

Peer::Peer(int port_number, const char *server_ip, int server_port, MainWindow *w): port_number(port_number), server_ip(server_ip), server_port(server_port), w(w) {    
    if( (server_socket_ID = ::socket(AF_INET , SOCK_STREAM , 0)) == 0) {   
        puts("Peer::Peer: failed to create socket");
    }   

    struct sockaddr_in address;
    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = INADDR_ANY;   
    address.sin_port = htons(port_number);

    if (::bind(server_socket_ID, (struct sockaddr *) &address, sizeof(address)) < 0)   
    {   
        puts("Peer::Peer: failed to bind");
        perror("bind failed");   
        exit(EXIT_FAILURE);   
    }   
    printf("Listener on port %d \n", port_number);

    if (::listen(server_socket_ID, MAX_PENDING) < 0)    {
        puts("Peer::Peer: failed to listen");
        perror("listen");   
        exit(EXIT_FAILURE);   
    }

    // Connect to all connected peers
    std::vector<std::pair<std::string, int> > connected_ip = GetConnectedIP(); 
    for(int i = 0; i < connected_ip.size(); i++) {
        this->Connect(connected_ip[i].first, connected_ip[i].second);
    }

    server_thread = std::thread(&Peer::accept, std::ref(*this));
}

Peer::~Peer() {
    server_thread.join();
    this->leave();
}

void Peer::accept() {
    int i, sd, activity, new_socket, addrlen, valread;
    char buffer[1025];

    struct sockaddr_in address;
    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = INADDR_ANY;   
    address.sin_port = htons( port_number );

    //accept the incoming connection  
    puts("Waiting for connections ...");

    while(true) {
        //clear the socket set  
        FD_ZERO(&readfds);   
     
        //add master socket to set  
        FD_SET(server_socket_ID, &readfds);   
        max_sd = server_socket_ID;   
             
        //add child sockets to set  
        for ( i = 0 ; i < client_sock_IDs.size() ; i++) {   
            //socket descriptor  
            sd = client_sock_IDs[i];   
                 
            //if valid socket descriptor then add to read list  
            if(sd > 0)   
                FD_SET( sd , &readfds);   
                 
            //highest file descriptor number, need it for the select function  
            if(sd > max_sd)   
                max_sd = sd;   
        }   
     
        //wait for an activity on one of the sockets , timeout is NULL ,  
        //so wait indefinitely  
        activity = ::select( max_sd + 1 , &readfds , NULL , NULL , NULL);   
       
        if ((activity < 0) && (errno!=EINTR)) {
            printf("select error");   
        }   
             
        //If something happened on the master socket ,  
        //then its an incoming connection  
        if (FD_ISSET(server_socket_ID, &readfds)) { 
            if ((new_socket = ::accept(server_socket_ID, (struct sockaddr *) &address, (socklen_t*) &addrlen)) < 0) {   
                puts("Peer::accept: failed to accept incoming connection");
                return;
            }   
             
            //inform user of socket number - used in send and receive commands  
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs 
                  (address.sin_port));   

            std::string messageString = "ewelu";
            const char *message = messageString.c_str();

            //send new connection greeting message  
            if( ::send(new_socket, message, strlen(message), 0) != strlen(message)) {
                perror("send");   
            }   
                 
            puts("Welcome message sent successfully"); 

            client_sock_IDs.push_back(new_socket);  
            printf("Adding to list of sockets as %lu\n" , client_sock_IDs.size() - 1);
                 
        }   
             
        //else its some IO operation on some other socket 
        for (i = 0; i < client_sock_IDs.size(); i++) {
            sd = client_sock_IDs[i];   
                 
            if (FD_ISSET( sd , &readfds)) {
                //Check if it was for closing , and also read the  
                //incoming message  
                if ((valread = read( sd , buffer, 1024)) == 0) {
                    //Somebody disconnected , get his details and print  
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);   
                    printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr) , ntohs(address.sin_port));   
                         
                    //Close the socket and mark as 0 in list for reuse  
                    close( sd );   
                    client_sock_IDs.erase(client_sock_IDs.begin() + i); 
                } else { 
                    uint32_t action;
                    memcpy(&action, buffer, 4);
                    if(action == 1) {
                        crdt.RemoteInsert(buffer);
                        w->update = true;
                        w->update_text = true;
                    } else if(action == 2) {
                        crdt.RemoteDelete(buffer);
                        w->update = true;
                        w->update_text = true;
                    } else {
                        w->update = false;
                        w->update_text = false;
                        continue;
                    }
                }   
            }   
        }   
    }
}

void Peer::Send(char* payload, int size) const {
    for (auto sd: client_sock_IDs) {
        puts("sending");
        uint32_t action;
        char value;
        memcpy(&action, payload, 4);
        memcpy(&value, payload+4, 1);
        if( ::write(sd, payload, size ) != size) {
            puts("error");
            perror("send");
        }  
    }
}

int Peer::Connect(std::string host, int port) {
    int clientSockID;
    struct sockaddr_in address;
    struct hostent *server;

    if( (clientSockID = ::socket(AF_INET , SOCK_STREAM , 0)) == 0) {   
        puts("Peer::Connect: failed to create socket");  
        return -1; 
    }

    server = gethostbyname(host.c_str());

    address.sin_family = AF_INET;   
    bcopy((char *)server->h_addr, 
         (char *)&address.sin_addr.s_addr,
         server->h_length);  
    address.sin_port = htons(port);

    if( (::connect(clientSockID , (struct sockaddr *) &address, sizeof(address))) < 0) {   
        puts("Peer::Connect: failed to connect"); 
        return -1;
    }

    client_sock_IDs.push_back(clientSockID);

    printf("Connected to host %s:%d\n", host.c_str(), port);

    return 0;
}

std::vector<std::pair<std::string, int> > Peer::GetConnectedIP() {
    std::vector<std::pair<std::string, int> > res;
    char *test = (char*) malloc(1024);
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    std::pair<int, int> payload;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(server_ip);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(server_port);
    if (::connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    payload = std::make_pair(0, port_number);
    n = write(sockfd, &payload, sizeof(std::pair<int, int>));
    if (n < 0) 
         error("ERROR writing to socket");
    n = read(sockfd, test, 1024);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%d\n", n);

    // deserialize
    uint32_t size;
    int counter = 4;
    memcpy(&size, test, 4);
    for (int i = 0; i < size; i++) {
        uint32_t res_ip;
        uint32_t port;
        struct in_addr sin_addr;
        char *host = (char *) malloc(10 * sizeof(char));

        memcpy(&res_ip, test + counter, 4);
        memcpy(&port, test + counter + 4, 4);

        sin_addr.s_addr = ntohl(res_ip);
        host = inet_ntoa(sin_addr);
        res.push_back(std::make_pair(host, (int) port));
        counter += 8;
    }

    for (int i = 0; i < res.size(); i++) {
        printf("HOST %s, PORT %d\n", res[i].first.c_str(), res[i].second);
    }
    
    close(sockfd);
    return res;
}

void Peer::leave() {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    std::pair<int, int> payload;
    portno = atoi("8080");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("0.0.0.0");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (::connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    payload = std::make_pair(-1, port_number);
    n = write(sockfd, &payload, sizeof(std::pair<int, int>));
    if (n < 0) 
         error("ERROR writing to socket");
    
    close(sockfd);
}

void Peer::Test() {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int a, b;

    std::pair<int, int> payload;
    portno = atoi("8080");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("0.0.0.0");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (::connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message1: ");
    scanf("%d", &a);
    printf("Please enter the message2: ");
    scanf("%d", &b);
    payload = std::make_pair(a, b);
    n = write(sockfd, &payload, sizeof(std::pair<int, int>));
    if (n < 0) 
         error("ERROR writing to socket");
    
    close(sockfd);
}
