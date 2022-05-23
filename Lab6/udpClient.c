#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(){

    int c = 0;
    char buff1[100], buff2[100];
    struct sockaddr_in serv_addr;
    int servfd = socket(AF_INET, SOCK_DGRAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(5000);
    int serv_length = sizeof(serv_addr);
    bzero(buff1, sizeof(buff1));
    bzero(buff2, sizeof(buff2));
printf("Msg from client : ");
    fgets(buff2, 100, stdin);
    sendto(servfd, &buff2, sizeof(buff2), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    bzero(buff2, sizeof(buff2));
    printf("Msg to client : ");
    recvfrom(servfd, &buff1, sizeof(buff1), 0, (struct sockaddr *)&serv_addr, &serv_length);

    puts(buff1);
    bzero(buff1, sizeof(buff1));
    printf("UDP Client Disconnected");
    return 0;
}

