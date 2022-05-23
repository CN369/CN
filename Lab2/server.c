#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
 
void func(int connfd)
{
	char buff[MAX];
	int n; 
	for (;;) {
		bzero(buff, MAX);
		read(connfd, buff, sizeof(buff)); 
		printf("Message From client: %s\t Reply To client : ", buff);
		bzero(buff, MAX);
		n = 0; 
		while ((buff[n++] = getchar()) != '\n')
			; 
		write(connfd, buff, sizeof(buff));
		if (strncmp("Exit", buff, 4) == 0) {
			printf("Server Exit.\n");
			break;
		}
	}
}
 
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;
	 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Failed to create socket.\n");
		exit(0);
	}
	else
		printf("Socket created successfully.\n");
	bzero(&servaddr, sizeof(servaddr));
 
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Failed to bind the socket.\n");
		exit(0);
	}
	else
		printf("Socket binded successfully.\n");
 
	if ((listen(sockfd, 5)) != 0) {
		printf("Server Listen failed.\n");
		exit(0);
	}
	else
		printf("Server is listening.\n");
	len = sizeof(cli);
 
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("Server accept failed.\n");
		exit(0);
	}
	else
		printf("Server accepted the client connection.\n");
 
	func(connfd);
 
	close(sockfd);
}

