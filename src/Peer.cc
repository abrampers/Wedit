#include "Peer.h"

void error(const char *msg) {
    perror(msg);
    exit(0);
}

Peer::Peer(int portNumber): portNumber(portNumber) {    
    if( (serverSocketID = ::socket(AF_INET , SOCK_STREAM , 0)) == 0) {   
        puts("Peer::Peer: failed to create socket");
        // perror("socket failed");   
        // exit(EXIT_FAILURE);   
    }   

    struct sockaddr_in address;
    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = INADDR_ANY;   
    address.sin_port = htons( portNumber );

    if (::bind(serverSocketID, (struct sockaddr *) &address, sizeof(address)) < 0)   
    {   
        puts("Peer::Peer: failed to bind");
        // perror("bind failed");   
        // exit(EXIT_FAILURE);   
    }   
    printf("Listener on port %d \n", portNumber);

    if (::listen(serverSocketID, MAX_PENDING) < 0)    {
        puts("Peer::Peer: failed to listen");
        // perror("listen");   
        // exit(EXIT_FAILURE);   
    }

    // Connect to all connected peers
    std::vector<std::pair<std::string, int> > connected_ip; 

    // this->accept();
    serverThread = std::thread(&Peer::accept, std::ref(*this));
}

Peer::~Peer() {
    serverThread.join();
    this->leave();
}

void Peer::accept() {
    int i, sd, activity, new_socket, addrlen, valread;
    char buffer[1025];

    struct sockaddr_in address;
    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = INADDR_ANY;   
    address.sin_port = htons( portNumber );

    //accept the incoming connection  
    puts("Waiting for connections ...");

    while(true) {
        //clear the socket set  
        FD_ZERO(&readfds);   
     
        //add master socket to set  
        FD_SET(serverSocketID, &readfds);   
        max_sd = serverSocketID;   
             
        //add child sockets to set  
        for ( i = 0 ; i < clientSockIDs.size() ; i++) {   
            //socket descriptor  
            sd = clientSockIDs[i];   
                 
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
        if (FD_ISSET(serverSocketID, &readfds)) { 
            if ((new_socket = ::accept(serverSocketID, (struct sockaddr *) &address, (socklen_t*) &addrlen)) < 0) {   
                puts("Peer::accept: failed to accept incoming connection");
                return;
                // perror("accept");   
                // exit(EXIT_FAILURE);   
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

            clientSockIDs.push_back(new_socket);  
            printf("Adding to list of sockets as %lu\n" , clientSockIDs.size() - 1);
                 
        }   
             
        //else its some IO operation on some other socket 
        for (i = 0; i < clientSockIDs.size(); i++) {
            sd = clientSockIDs[i];   
                 
            if (FD_ISSET( sd , &readfds)) {
                //Check if it was for closing , and also read the  
                //incoming message  
                if ((valread = read( sd , buffer, 1024)) == 0) {
                    //Somebody disconnected , get his details and print  
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);   
                    printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr) , ntohs(address.sin_port));   
                         
                    //Close the socket and mark as 0 in list for reuse  
                    close( sd );   
                    clientSockIDs.erase(clientSockIDs.begin() + i); 
                } else { 
                    //set the string terminating NULL byte on the end  
                    //of the data read  
                    buffer[valread] = '\0'; 
                    // Handle every incoming message here;

                    // printf(buffer);
                    // ::send(sd , buffer , strlen(buffer) , 0 );   
                }   
            }   
        }   
    }
}

void Peer::send(std::string payload) const {
    for (auto& sd: clientSockIDs) {
        if( ::send(sd, payload.c_str(), strlen(payload.c_str()), 0) != strlen(payload.c_str())) {
            perror("send");   
        }  
    }
}

int Peer::connect(std::string host, int port) {
    int clientSockID;
    struct sockaddr_in address;
    struct hostent *server;

    if( (clientSockID = ::socket(AF_INET , SOCK_STREAM , 0)) == 0) {   
        puts("Peer::connect: failed to create socket");
        // perror("socket failed");   
        // exit(EXIT_FAILURE);  
        return -1; 
    }

    server = gethostbyname(host.c_str());

    address.sin_family = AF_INET;   
    bcopy((char *)server->h_addr, 
         (char *)&address.sin_addr.s_addr,
         server->h_length);  
    address.sin_port = htons(port);

    if( (::connect(clientSockID , (struct sockaddr *) &address, sizeof(address))) < 0) {   
        puts("Peer::connect: failed to connect");
        // perror("connect failed");   
        // exit(EXIT_FAILURE);   
        return -1;
    }

    clientSockIDs.push_back(clientSockID);

    printf("Connected to host %s:%d\n", host.c_str(), port);

    return 0;
}

std::vector<std::pair<std::string, int> > Peer::getConnectedIP() {
    std::vector<std::pair<std::string, int> > res;
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    res.push_back(std::make_pair("0.0.0.0", 5000));


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
    printf("Please enter the message: ");
    payload = std::make_pair(0, portNumber);
    n = write(sockfd, &payload, sizeof(std::pair<int, int>));
    if (n < 0) 
         error("ERROR writing to socket");
    n = read(sockfd, &res, 1024);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%d\n", n);
    
    for(int i = 0; i < res.size(); i++) {
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
    payload = std::make_pair(-1, portNumber);
    n = write(sockfd, &payload, sizeof(std::pair<int, int>));
    if (n < 0) 
         error("ERROR writing to socket");
    
    close(sockfd);
}

void Peer::test() {
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