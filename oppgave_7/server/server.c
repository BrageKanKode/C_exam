#include "include/server.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

struct sockaddr_in saAddr = {0};      //Bind
struct sockaddr_in saConClient = {0}; //Accept

int main(int argc, char *argv[])
{
    struct hostent *server;
    int sockfd;
    int sockNewFd = 0;
    int iPort;
    int addrLen = sizeof(saAddr);
    int pid;
    int opt;

    //Checking if any argument is passed
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }

    // Check if argumtens are correct
    iPort = atoi(argv[2]);
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    //create a server socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("socket failed with %i\n", errno);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //Specify an address for the server
    saAddr.sin_family = AF_INET;
    saAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saAddr.sin_port = htons(iPort);

    if (bind(sockfd, (struct sockaddr *)&saAddr, sizeof(saAddr)) < 0)
    {
        printf("bind failed with %i\n", errno);
    }

    listen(sockfd, 5);

    //Infinite while loop to handle more connections
    while (1)
    {
        sockNewFd = accept(sockfd, (struct sockaddr *)&saConClient, (socklen_t *)&addrLen);
        if (sockNewFd < 0)
        {
            printf("accept failed with %i\n", errno);
        }
        pid = fork();
        if (pid < 0)
        {
            printf("Error on fork");
        }
        if (pid == 0)
        {
            printf("Client connected\n");
            dostuff(sockNewFd, argv[1], iPort);
            close(sockfd);
            exit(0);
        }
        else
            close(sockNewFd);
    }

    close(sockNewFd);
    sockfd = -1;
    close(sockfd);
    sockfd = -1;
    return 0;
}

void dostuff(int socket, char *serverAddress, int iPort)
{
    char buffer[256];
    char server_message[256];
    int readvalue;
    int iWannaTalk = -1;

    sprintf(server_message, "You have reached the server '%s' on port '%d'\n"
                            "Would you like to continue?(Y/N)",
            serverAddress, iPort);
    //strcpy(server_message, "You have reached the server on port 127.0.0.1\n Would you like to continue?(Y/N)");
    send(socket, server_message, sizeof(server_message), 0);

    //Set buffer to 0 and use it to read the value from client
    memset(buffer, 0, 256);
    readvalue = read(socket, buffer, 256 - 1);

    if (readvalue < 0)
    {
        printf("read failed with %i\n", errno);
        strcpy(server_message, "Failed to read input");
        printf("Client disconnected\n");
        send(socket, server_message, sizeof(server_message), 0);
        return;
    }
    printf("Client said: %s", buffer);

    if (strncmp(buffer, "Y", strlen(buffer) - 1) == 0 || strncmp(buffer, "y", strlen(buffer) - 1) == 0)
    {
        strcpy(server_message, "Hello there!");
        iWannaTalk = 0;
        send(socket, server_message, sizeof(server_message), 0);
    }
    else
    {
        strcpy(server_message, "Goodbye...");
        printf("\nClient disconnected\n");
        send(socket, server_message, sizeof(server_message), 0);
        return;
    }

    while (iWannaTalk == 0)
    {
        strcpy(server_message, "still connected");
        send(socket, server_message, sizeof(server_message), 0);
        memset(buffer, 0, 256);
        readvalue = read(socket, buffer, 256 - 1);
        if (readvalue < 0)
        {
            printf("read failed with %i\n", errno);
        }
        if (strncmp(buffer, "goodbye", strlen(buffer) - 1) == 0 || strncmp(buffer, "", strlen(buffer) - 1) == 0)
        {
            printf("Client disconnected\n");
            iWannaTalk = -1;
            break;
        }
        printf("Client said: %s", buffer);
    }
}