#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
//using namespace std;

#define PORT 8080

int main(){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
        printf("socket failed\n");
        return 0;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //any address
    address.sin_port = htons(PORT);
    int bindstat = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    if (bindstat < 0) {
        return 0;
    }
    if (listen(server_fd, 5) < 0) {
        return 0;
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
        return 0;
    }
    struct timeval start, curr, end;
    gettimeofday(&start, NULL);
    int points = 0;
    char data[1024];
    while (1) {
        valread = recv(new_socket, (char*) &buffer, 1024, 0);
        if (!strcmp(buffer, "exit")) break;
        gettimeofday(&curr, NULL);
        double elapsed = (double)(curr.tv_usec - start.tv_usec) / 1000000 + (double)(curr.tv_sec - start.tv_sec);
        printf("Received this message at %f seconds: %s\n", elapsed, buffer);
        int num = 0;
        bool f = 0;
        for (int i = 0; i < strlen(buffer); i++){
            if ((int)buffer[i] - '0' >= 0 && (int)buffer[i] - '0' < 10) num = 10 * num + ((int)buffer[i] - '0');
            else {
                f = 1;
                break;
            }
        }
        std::string msg;
        memset(&data, 0, sizeof(data));
        if (f) {
            msg = "Only int allowed!!!";
        }
        else {
            if ((int) elapsed == num) {
                points++;
                msg = "GOOD JOB! You have " + std::to_string(points) + " points.";
            }
            else{
                msg = "WRONG! You have " + std::to_string(points) + " points.";
            }
        }
        strcpy(data, msg.c_str());
        send(new_socket, (char*)&data, strlen(data), 0);
        memset(&buffer, 0, sizeof(buffer));
    }
    printf("\n");
    gettimeofday(&end, NULL);
    double esecs = (double)(end.tv_usec - start.tv_usec) / 1000000 + (double)(end.tv_sec - start.tv_sec);
    printf("Client ended connection at %f seconds \n", esecs);
    close(new_socket);
    close(server_fd);
    return 0;
}
