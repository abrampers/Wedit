// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <utility>
#include <vector>
#include <string>
#include <arpa/inet.h>
#include <iostream>
const int PORT = 8080;

char* serialize(std::vector<std::pair<std::string, int> > input) {
    std::vector<std::pair<uint32_t, uint32_t>> connected_ip;
    struct sockaddr_in ip4addr;
    ip4addr.sin_family = AF_INET;

    for (auto e: input) {
        inet_pton(AF_INET, e.first.c_str(), &ip4addr.sin_addr);
        uint32_t res_ip = htonl(ip4addr.sin_addr.s_addr);
        connected_ip.push_back(std::make_pair(res_ip, (uint32_t) e.second));
    }

    uint32_t size = (uint32_t) connected_ip.size();
    int counter = 4;
    char* data = (char*) malloc(4 + (connected_ip.size() * 8));

    memcpy(data, &size, 4);
    for (auto e: connected_ip) {
        memcpy(data + counter, &e.first, 4);
        memcpy(data + counter + 4, &e.second, 4);
        counter += 8;
    }
    return data;
}

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *host = (char *) malloc(10 * sizeof(char));
    int port;
    std::pair<int, int> request;

    std::vector<std::pair<std::string, int> > connected_ip;
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    printf("Listener on port %d \n", PORT);
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 

    puts("Waiting for connections ...");

    while(true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                        (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 
        valread = read(new_socket, &request, sizeof(std::pair<int, int>)); 
        printf("%d, %d\n", request.first, request.second); 

        if (request.first == 0) {
            puts("adding peer");
            // reply request and add
            memset(host, 0, sizeof(host));
            port = request.second;
            host = inet_ntoa(address.sin_addr);

            // serialize data
            char* data = serialize(connected_ip);
            uint32_t size;

            memcpy(&size, data, 4);
            if(write(new_socket, data, 4 + (connected_ip.size() * 8)) < 0) {
                puts("Succes write!!");
            }
            connected_ip.push_back(std::make_pair(std::string(host), port));
            printf("Peer %s, %d successfully added\n", host, port);
        } else if (request.first == -1) {
            puts("deleting peer");
            memset(host, 0, sizeof(host));
            port = request.second;
            host = inet_ntoa(address.sin_addr);
            bool found = false;
            for(int i = 0; i < connected_ip.size(); i++) {
                if (connected_ip[i].first == host && connected_ip[i].second == port) {
                    connected_ip.erase(connected_ip.begin() + i); 
                    found = true;
                    break;
                }
            }
            if (found) 
                printf("Peer %s, %d successfully deleted\n", host, port);
        } else {
            puts("showing peers");
            for(int i = 0; i < connected_ip.size(); i++) {
                printf("%s, %d\n", connected_ip[i].first.c_str(), connected_ip[i].second);
            }
        }
    }

    free(host);
    return 0; 
} 
