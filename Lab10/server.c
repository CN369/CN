#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<netinet/in.h> 
#include<sys/socket.h> 
#include<sys/types.h>

int main()
{
int c=0;
char buff1[100],buff2[100];
struct sockaddr_in serv_addr,cli_addr;
int servfd=socket(AF_INET,SOCK_STREAM,0); 
bzero(&serv_addr,sizeof(serv_addr)); 
bzero(&cli_addr,sizeof(cli_addr));

serv_addr.sin_family=AF_INET; 
serv_addr.sin_addr.s_addr=inet_addr("0.0.0.0"); 
serv_addr.sin_port=htons(8000);

int x=bind(servfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr)); 
if(x==-1)
{
printf("Bind error"); 
return 1;
}

int x1=listen(servfd,5); if(x1==-1)
{
printf("\nError"); return 1;
}
int s1=sizeof(cli_addr);
int x2=accept(servfd,(struct sockaddr *)&cli_addr,&s1);
 
getpeername(x2,(struct sockaddr *)&cli_addr,&s1); 
char *ch=malloc(100); 
inet_ntop(AF_INET,&cli_addr.sin_addr,ch,100); 
printf("Client IP Address= %s\n",ch);
bzero(buff1,sizeof(buff1)); 
bzero(buff2,sizeof(buff2)); 
printf("Msg %d to server: ",c); 
read(x2,buff1,sizeof(buff1)); 
puts(buff1); 
bzero(buff1,sizeof(buff1)); 
printf("Msg %d from server: ",c); 
fgets(buff2,100,stdin); 
write(x2,buff2,sizeof(buff2)); 
bzero(buff2,sizeof(buff2));
return 0;
}

