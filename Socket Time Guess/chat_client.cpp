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
using namespace std;

#define PORT 8080

int main(){
    int sock, valread;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){ //creat socket with TCP connection
        cout << "Connection error" << endl;
        return 0;
    }
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET; //ipv4
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "10.19.31.84", &serv_addr.sin_addr) <= 0){ //local ip
        cout << "Address not supported" << endl;
        return 0;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        cout << "Connection Failed" << endl;
        return 0;
    }
    cout << "Connected. Guess how many seconds elapsed!\n" << endl;
    char msg[1024], buffer[1024];
    struct timeval start, end;
    gettimeofday(&start, NULL);
    while (1) {
        string data;
        getline(cin, data);
        memset(&msg, 0, sizeof(msg));
        memset(&buffer, 0, sizeof(buffer));
        strcpy(msg, data.c_str());
        send(sock, (char *) &msg, strlen(msg), 0);
        if (data == "exit") break;
        valread = recv(sock, (char*) &buffer, 1024, 0);
        printf("Server: %s\n", buffer);
    }
    printf("\n");
    gettimeofday(&end, NULL);
    double esecs = (double)(end.tv_usec - start.tv_usec) / 1000000 + (double)(end.tv_sec - start.tv_sec);
    printf("Ended connection at %f seconds \n", esecs);
}