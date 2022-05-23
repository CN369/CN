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
struct sockaddr_in serv_addr;
int servfd=socket(AF_INET,SOCK_STREAM,0); 
serv_addr.sin_family=AF_INET; 
serv_addr.sin_addr.s_addr=inet_addr("0.0.0.0"); 
serv_addr.sin_port=htons(8000);

int n=connect(servfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)); 
if(n==0)
{
printf("connection established\n");
}
else 
printf("error\n");

bzero(buff1,sizeof(buff1)); 
bzero(buff2,sizeof(buff2));
 
printf("msg %d from client: ",c); 
fgets(buff2,100,stdin); 
write(servfd,buff2,sizeof(buff2)); 
bzero(buff2,sizeof(buff2)); 
printf("msg %d to client: ",c); 
read(servfd,buff1,sizeof(buff1)); 
puts(buff1); 
bzero(buff1,sizeof(buff1));

return 0;
}

