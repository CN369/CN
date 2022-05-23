#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int c = 0;
    char buff1[100], buff2[100];
    struct sockaddr_in serv_addr, cli_addr;
    int servfd = socket(AF_INET, SOCK_DGRAM, 0);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(5001);
    serv_addr.sin_family = AF_INET;
    int serv_length = sizeof(serv_addr);
    int n=connect(servfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(n==0){
        printf("Connection Established\n");
    }else{
        printf("Error");
        return -1;
    }
    while(1){
        c++;
        bzero(buff1, sizeof(buff1));
        bzero(buff2, sizeof(buff2));
        printf("Msg %d from Client: ", c);
        fgets(buff2, 100, stdin);
        sendto(servfd, &buff2, sizeof(buff2), 0, (struct sockaddr *)NULL, 0);
        printf("Msg %d to Client: ", c);
        recvfrom(servfd, &buff1, sizeof(buff1), 0, (struct sockaddr *)NULL, 0);
        puts(buff1);
        bzero(buff1, sizeof(buff1));
        if (c == 2)
            break;
    }
    return 0;
}
