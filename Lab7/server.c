#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
    int c = 0, c1 = 1, servfd;
    servfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    struct sockaddr_un serv_addr, cli_addr;
    unlink("/tmp/unix.str");
    char buff1[100], buff2[100];
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_LOCAL;
    strcpy(serv_addr.sun_path, "/tmp/unix.str");
    int x = bind(servfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (x == -1)
    {
        printf("Bind error\n");
        return 1;
    }
    int cli_len = sizeof(cli_addr);
    bzero(buff1, sizeof(buff1));
    bzero(buff2, sizeof(buff2));
    printf("Msg to server: ");
    recvfrom(servfd, &buff1, sizeof(buff1), 0, (struct sockaddr *)&cli_addr, &cli_len);
    puts(buff1);
    printf("Msg from server: ");
    fgets(buff2, 100, stdin);
    sendto(servfd, &buff2, sizeof(buff2), 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
    return 0;
}
