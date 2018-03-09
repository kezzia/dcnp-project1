#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

/* <server> <port> */
int main(int argc, char *argv[])
{
    if (argc != 2) {
      printf("Looking for a command of format: %s <port>\n", argv[0]);
      return 1;
    }

    int n = 0;

    int port_num = atoi(argv[1]);
    printf("Starting server on port number %i\n", port_num);
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1024];
    char recvBuff[1024];

    /* creating socket and socket descriptor that uses IPv4 address and TCP*/
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    /* family/domain to be used by listening socket */
    serv_addr.sin_family = AF_INET;
    /* interface the socket will listen on */
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* port on which server will wait for clients */
    serv_addr.sin_port = htons(port_num);

    /* assigns the details specified in the struct ‘serv_addr’ to the socket
     listenfd. */
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    /* Up to 5 clients are allowed queue for the listening socket*/
    listen(listenfd, 5);

    /* We need an infinite loop so that the server is always running */
    while (1) {
        /* the server is put to sleep and waits for a client request. When the
        three way TCP handshake* is complete, the socket descriptor representing
        the client socket is returned. */
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

        /* server sends message to client's socket through clients socket descriptor
        and client can read it through normal read call on the its socket
        descriptor. */
        while ((n = read(connfd, recvBuff, sizeof(recvBuff)-1)) > 0) {
            recvBuff[n] = 0;
            if(fputs(recvBuff, stdout) == EOF)
            {
                printf("\n Error : Fputs error\n");
            }
        }

        if (n < 0) {
            printf("\n Read error \n");
        }

        printf("\nMessage received!\n");
        /* this apparently ensures that server does not eat up all of your CPU
        processing. [Waka Flocka voice] OK. */
        sleep(1);
     }
}
