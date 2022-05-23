#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int i, c = 0, c1 = 1, len, n;
    int nready, cl[FD_SETSIZE], maxi, maxfd;
    fd_set rset, allset;
    int listenfd, connfd, sockfd;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    char buff1[100], buff2[100];
    struct sockaddr_in serv_addr, cli_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    bzero(&cli_addr, sizeof(cli_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(5000);

    int x = bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (x == -1)
    {
        printf("bind error");
        return 1;
    }

    int x1 = listen(listenfd, 5);
    if (x1 == -1)
    {
        printf("\nerror");
        return 1;
    }
    maxfd = listenfd;
    maxi = -1;

    for (i = 0; i < FD_SETSIZE; i++)
        cl[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    for (;;)
    {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &rset))
        {
            len = sizeof(cli_addr);
            connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &len);

            for (i = 0; i < FD_SETSIZE; i++)
                if (cl[i] < 0)
                {
                    cl[i] = connfd;
                    break;
                }
            if (i == FD_SETSIZE)
                printf("too many clients");

            FD_SET(connfd, &allset);
            if (connfd > maxfd)
                maxfd = connfd;
            if (i > maxi)
                maxi = i;

            if (--nready <= 0)
                continue;
        }

        for (i = 0; i <= maxi; i++)
        {
            if ((sockfd = cl[i]) < 0)
                continue;
            if (FD_ISSET(sockfd, &rset))
            {
                printf("msg from client to server: ");
                read(sockfd, buff1, 100);
                puts(buff1);
                printf("msg from server to client: ");
                fgets(buff2, 100, stdin);
                write(sockfd, buff2, 100);

                close(sockfd);

                FD_CLR(sockfd, &allset);
                cl[i] = -1;
                if (--nready <= 0)
                {
                    break;
                }
            }
        }
    }
    return 0;
}

