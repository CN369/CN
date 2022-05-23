#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

int main()
{

    int c = 0;
    char buff1[100], buff2[100];
    struct sockaddr_un serv_addr, cli_addr;
    int servfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    bzero(&cli_addr, sizeof(cli_addr));

    cli_addr.sun_family = AF_LOCAL;
    strcpy(cli_addr.sun_path, tmpnam(NULL));
    int x = bind(servfd, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
    if (x == -1)
    {
        printf("Bind Error");
        return -1;
    }
     bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_LOCAL;
    strcpy(serv_addr.sun_path, "/tmp/unix.str");

    int serv_len = sizeof(serv_addr);
    bzero(buff1, sizeof(buff1));
    bzero(buff2, sizeof(buff2));
    printf("Msg from client : ");
    fgets(buff2, 100, stdin);
sendto(servfd, &buff2, sizeof(buff2), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    bzero(buff2, sizeof(buff2));
    printf("Msg to client : ");
    recvfrom(servfd, &buff1, sizeof(buff1), 0, (struct sockaddr *)&serv_addr, &serv_len);
    puts(buff1);
    bzero(buff1, sizeof(buff1));
    return 0;
}

