#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
void siga(int signo)
{
    printf("Read error\n");
    exit(1);
}
int main()
{
    int c = 0;
    char buff1[100], buff2[100];
    struct sockaddr_in serv_addr;
    int servfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(5000);

    int n = connect(servfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (n == 0)
    {
        printf("Connection established\n");
    }
    else
        printf("Error\n");
    signal(SIGALRM, siga);
    bzero(buff1, sizeof(buff1));
    bzero(buff2, sizeof(buff2));
    printf("Msg from client: ");
    fgets(buff2, 100, stdin);
    write(servfd, buff2, sizeof(buff2));
    bzero(buff2, sizeof(buff2));
    printf("Msg to client: ");
    alarm(10);
    sleep(5);
    read(servfd, buff1, sizeof(buff1));
    puts(buff1);
    bzero(buff1, sizeof(buff1));

    return 0;
}
