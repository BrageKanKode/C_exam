#include "include/client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <errno.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{

    struct sockaddr_in saAddr; //Connect
    int sockFd;
    int iPort = atoi(argv[1]);
    char msg[256];
    char server_response[256];
    char *unused;

    //Check if arguments are less than 2
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(0);
    }

    //create socket
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0)
    {
        printf("socket failed with %i\n", errno);
    }

    //Define the socket address

    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);
    saAddr.sin_addr.s_addr = INADDR_ANY;

    //check for error with the connections
    if (connect(sockFd, (struct sockaddr *)&saAddr, sizeof(saAddr)) < 0)
    {
        printf("connect failed with %i\n", errno);
        return -1;
    }

    //recieve data from the server
    recv(sockFd, &server_response, sizeof(server_response), 0);

    //print out the server's response
    printf("Server: %s\n", server_response);

    unused = fgets(msg, sizeof(msg), stdin);
    send(sockFd, msg, strlen(msg), 0);

    // Set server_response to 0 and recieve a new messge
    memset(server_response, 0, 256);
    recv(sockFd, &server_response, sizeof(server_response), 0);
    printf("Server: %s\n", server_response);

    // Now send messages to the server
    while (strncmp(server_response, "Goodbye...", strlen(server_response) - 1) != 0)
    {
        // Server lets us know it's still listening
        memset(server_response, 0, 256);
        recv(sockFd, &server_response, sizeof(server_response), 0);
        if (strncmp(server_response, "still connected", strlen(server_response) - 1) != 0)
        {
            printf("server disconnected\n");
            break;
        }

        //Send it message
        printf("Type in server message;\n");
        unused = fgets(msg, sizeof(msg), stdin);
        send(sockFd, msg, strlen(msg), 0);

        // Don't want to stay connected anymore
        if (strcmp(msg, "goodbye") == 0)
        {
            break;
        }
    }

    close(sockFd);
    sockFd = -1;

    return 0;
}