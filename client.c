#include<stdio.h>    
#include<sys/socket.h>    
#include<arpa/inet.h> 
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>



int main(int argc, char *argv[])
{
	int sock, length,n;
	struct sockaddr_in server, from;
	struct hostent *hp;
	char buffer[256];
	
	if (argc != 3)
	{
		printf("usage: server port\n");
		exit(1);
	}
	sock=socket(AF_INET, SOCK_DGRAM, 0);
	
	
	server.sin_family = AF_INET;
    hp =gethostbyname(argv[1]);
	
	if (hp==0)
	{
		error("unkown host");
	}
	
	bcopy((char *)hp->h_addr, (char *)&server.sin_addr,hp->h_length);
	server.sin_port=htons(atoi(argv[2]));
	length=sizeof(struct sockaddr_in);
	while(1)
	{
	printf("please enter your bid: ");
	
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	n=sendto(sock,buffer,strlen(buffer),0,&server,length);
	
	if (n < 0)
	{
		error("sendto");
	}
	
 n=recvfrom(sock,buffer,256,0,&from,&length);
 if (n < 0)
 {
	 error("recvfrom");
 }
 write(1,"got a reply: ",12);
 printf("current bid is %s \n",buffer);
}

}
