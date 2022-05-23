#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}
void err_sys(const char *x)
{
    perror(x);
    exit(1);
}

int main()
{
    int c = 0, c1 = 1, len, n;
    pid_t pid;
    fd_set rset;

    int listenfd, connfd, udpfd, nready, maxfdpl;
    char msg[100];
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    char buff1[100], buff2[100];

    struct sockaddr_in serv_addr, cli_addr;

    bzero(&serv_addr, sizeof(serv_addr));
    bzero(&cli_addr, sizeof(cli_addr));
    serv_addr.sin_family = AF_INET;

    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 5);

    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(5000);

    bind(udpfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    FD_ZERO(&rset);
    maxfdpl = max(listenfd, udpfd) + 1;

    while (1)
    {
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);

        if (nready = select(maxfdpl, &rset, NULL, NULL, NULL) < 0)
        {
            if (errno == EINTR)
                continue;
            else
                err_sys("select error\n");
        }

        if (FD_ISSET(listenfd, &rset))
        {
            len = sizeof(cli_addr);
            connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &len);
            bzero(buff1, sizeof(buff1));
            bzero(buff2, sizeof(buff2));
            if ((pid = fork()) == 0)
            {
                close(listenfd);
                printf("msg from TCP client to server: ");
if ((read(connfd, buff1, sizeof(buff1)) < 0))
                {
                    perror("Error: ");
                    return (-1);
                }
                else
                    puts(buff1);

                printf("msg from server to TCP client: ");
                fgets(buff2, 100, stdin);
                if ((write(connfd, buff2, sizeof(buff2)) < 0))
                {
                    perror("Error: ");
                    return (-1);
                }
close(connfd);
                exit(0);
            }
            close(connfd);
        }
        if (FD_ISSET(udpfd, &rset))
        {
            len = sizeof(cli_addr);
            printf("msg from UDP client to server: ");
            recvfrom(udpfd, &buff1, sizeof(buff1), 0, (struct sockaddr *)&cli_addr, &len);
puts(buff1);
            printf("msg from server to UDP client: ");
            fgets(buff2, 100, stdin);
            sendto(udpfd, &buff2, sizeof(buff2), 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
        }
    }
    return 0;
}

