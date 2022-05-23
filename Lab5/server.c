#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
int c=0,c1=-1;
pid_t pid;
int servfd,connfd;
servfd=socket(AF_INET,SOCK_STREAM,0);
char buff1[100],buff2[100];
struct sockaddr_in serv_addr,cli_addr;
bzero(&serv_addr,sizeof(serv_addr));
bzero(&cli_addr,sizeof(cli_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=INADDR_ANY;
serv_addr.sin_port=htons(5000);
int x=bind(servfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
if(x==-1)
{
printf("bind error");
return 1;
}
int x1=listen(servfd,5);
if(x1==-1){
printf("\n error");
return 1;
}
printf("Waiting for a connection...\n");
 listen(servfd, 5);
for(;;)
{
int s1=sizeof(cli_addr);
connfd=accept(servfd,(struct sockaddr *)&cli_addr,&s1);
if (connfd < 0) {
   printf("Error accepting connection!\n");
   exit(1);
  }
 printf("Connection accepted...\n");
bzero(buff1,sizeof(buff1));
bzero(buff2,sizeof(buff2));
if((pid=fork())==0)
{
close(servfd);
printf("message from client to server:");
read(connfd,buff1,sizeof(buff1));
puts(buff1);
printf("message from server to client:");
fgets(buff2,100,stdin);
write(connfd,buff2,sizeof(buff2));
close(connfd);
exit(0);
}
close(connfd);
}
return 0;
}
