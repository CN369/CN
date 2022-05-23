#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
int main()
{
    int c = 0;
    char buff1[100], buff2[100];
    struct sockaddr_in serv_addr, cli_addr;
    int servfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&serv_addr, sizeof(serv_addr));
    bzero(&cli_addr, sizeof(cli_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(5000);
    int x = bind(servfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (x == -1)
    {
        printf("Bind error");
        return 1;
    }
    int cli_length = sizeof(cli_addr);
    printf("Msg to server: ");
    recvfrom(servfd, &buff1, sizeof(buff1), 0, (struct sockaddr *)&cli_addr, &cli_length);
    puts(buff1);
    printf("Msg from server:");
    fgets(buff2, 100, stdin);
    sendto(servfd, &buff2, sizeof(buff2), 0, (struct sockaddr *)&cli_addr,sizeof(cli_addr));
    return 0;
}
