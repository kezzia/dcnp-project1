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
#include "practice_project.h"

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
    char tempBuff[1024];
    char input_file_path[1024];
    char output_file_target[1024];
    int to_format;
    int param_number = 0;

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
            if (fputs(recvBuff, stdout) == EOF)
            {
                printf("\n Error : Fputs error\n");
            }

              /* Iterate through the string and add each char to a temp string.
              when we encounter a ? we know that the parameter has changed.
              param 0 = input_file_path
              param 1 = to_format
              param 2 = output_file_target
              when the prameter changes we stop copying characters into the temp
              string. Instead we copy the temp string into the correct variable,
              clear the temp string and start writing in it again.*/
              int temp_iterator = 0;
              int i;
              printf("\n");
              for (i = 0; i < strlen(recvBuff); i++) {
                if ((recvBuff[i] == '?') || (recvBuff[i] == '\0')) {
                  printf("\nCHARACTER FOUND AT INDEX %i\n", i);
                  strncpy(tempBuff, (recvBuff+temp_iterator),((i)-temp_iterator));
                  //printf("tempBuff:%s\n", tempBuff);
                  /* copy tempBuff into approrpriate string */
                  if (param_number == 0) {strcpy(input_file_path, tempBuff);}
                  if (param_number == 1) {to_format = atoi(tempBuff);}
                  //if (param_number == 2) {strcpy(output_file_target, tempBuff);}
                  param_number++;
                  /* reset tempBuff */
                  memset(tempBuff, 0, strlen(tempBuff));
                  /* Jump i forward 1 so it ignores the ? */
                  i++;
                  /* reset tempBuff's iterator */
                  temp_iterator = i;
                }
                //tempBuff[temp_iterator] = recvBuff[i];
                //printf("%c\n", tempBuff[i]);
              }
              strncpy(tempBuff, (recvBuff+temp_iterator),((i)-temp_iterator));
              strcpy(output_file_target, tempBuff);
              //printf("tempBuff:%s\n", tempBuff);

              printf("input_file_path is: %s\n", input_file_path);
              printf("to_format is: %i\n", to_format);
              printf("output_file_target is: %s\n", output_file_target);

            printf("\nMessage received!\n");
            if (to_format == 0) {
              type_0_translation(input_file_path, output_file_target);
            } else if (to_format == 1) {
              type_1_translation(input_file_path, output_file_target);
            } else if (to_format == 2) {
              type_2_translation(input_file_path, output_file_target);
            } else if (to_format == 3) {
            type_3_translation(input_file_path, output_file_target);
            }
        }

        if (n < 0) {
            printf("\n Read error \n");
        }

        /* this apparently ensures that server does not eat up all of your CPU
        processing. [Waka Flocka voice] OK. */
        sleep(1);
     }
}
