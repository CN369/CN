#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    struct sockaddr_in serv_addr, allegedserv;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&serv_addr, sizeof(serv_addr));
    bzero(&allegedserv, sizeof(allegedserv));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    char read_buff[100], write_buff[100];
    bzero(read_buff, sizeof(read_buff));
    bzero(write_buff, sizeof(write_buff));
    printf("Msg from client: ");
    fgets(write_buff, 100, stdin);
    int s = sizeof(serv_addr);
    int alen;
    char str[30] = {0}, str1[30] = {0};
    sendto(sockfd, write_buff, sizeof(write_buff), 0, (struct sockaddr *)&serv_addr, s);
    inet_ntop(AF_INET, &serv_addr.sin_addr, str1, s);
    bzero(write_buff, sizeof(write_buff));
    printf("Msg to client: ");
    recvfrom(sockfd, read_buff, sizeof(read_buff), 0, (struct sockaddr *)&allegedserv, &alen);
puts(read_buff);
    inet_ntop(AF_INET, &allegedserv.sin_addr, str, alen);
    if (s != alen || memcmp(&str, &str1, sizeof(str)) != 0)
        printf("Reply came from different server %s \n", str);
    else
        printf("It came from the same server %s \n", str);
    
    bzero(read_buff, sizeof(read_buff));
    return 0;
}
