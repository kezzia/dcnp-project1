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

/* <client> <server IP> <server port> <file path> <to format> <to name> */
int main(int argc, char *argv[]) {
    int sockfd = 0, n = 0, port_num = 0, to_format = 0;
    char recvBuff[1024];
    char sendBuff[1024];
    struct sockaddr_in serv_addr;
    char input_file_path[1024];
    char output_file_target[1024];
    char server_msg[1024];

    /* Ensuring that we receive the correct # of arguments from the user */
    if (argc != 6) {
        printf("\n Looking for a command of format: %s <server IP> <server port> <file path> <to format> <to name>\n", argv[0]);
        return 1;
    }

    /* Setting port # */
    port_num = atoi(argv[2]);
    /* Setting input file path*/
    strncpy(input_file_path, argv[3], strlen(argv[3]));
    /* Setting format */
    to_format = atoi(argv[4]);
    /* Setting output file target */
    strncpy(output_file_target, argv[5], strlen(argv[5]));

    if (to_format > 3) {
      printf("The format code you have entered is invalid/unsupported.\n");
      return 1;
    }

    /* creating a string with the 3 things we need to send to the server */
    sprintf(server_msg, "%s %i %s", input_file_path, to_format,
      output_file_target);

    memset(recvBuff, '0', sizeof(recvBuff));
    memset(sendBuff, '0', sizeof(sendBuff));

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

    /* client sends message to server through server's socket descriptor */
    snprintf(sendBuff, sizeof(sendBuff), server_msg);
    write(sockfd, sendBuff, strlen(sendBuff));

    close(sockfd);


    return 0;
}
