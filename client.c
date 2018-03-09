#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include "practice_project.h"

/* <client> <server IP> <server port> <file path> <to format> <to name> */
int main(int argc, char *argv[]) {
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr;

    /* Ensuring that we receive the correct # of arguments from the user */
    if (argc != 6) {
        printf("\n Looking for a command of format: %s <server IP> <server port> <file path> <to format> <to name>\n", argv[0]);
        return 1;
    }
    int port_num = atoi(argv[2]);

    memset(recvBuff, '0',sizeof(recvBuff));

    /* creating another socket and descriptor that uses IPv4 and TCP */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    /* IP address of the remote host */
    serv_addr.sin_family = AF_INET;
    /* Port of remote host */
    serv_addr.sin_port = htons(port_num);

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0) {
        printf("\n inet_pton error occured\n");
        return 1;
    }
    /* try to connect this socket with the socket of the remote host. */
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
       printf("\n Error : Connect Failed \n");
       return 1;
    }

    /* server sends message to client's socket through clients socket descriptor
    and client can read it through normal read call on the its socket
    descriptor. */
    while ((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0) {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    }

    if (n < 0) {
        printf("\n Read error \n");
    }

    return 0;
}
