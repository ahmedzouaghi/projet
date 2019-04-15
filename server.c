#include<stdio.h>        
#include<sys/socket.h> 
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<pthread.h>
int sock, length, fromlen ,n,bet,bid;
struct sockaddr_in server;
struct sockaddr_in from;
char buf [1024];

void* serv_h(void* arg)
{
	bid=0;
while (1)
{
	
	n=recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
	printf("client biding is %s",buf);
	bet=atoi(buf);

	if (bid<bet){
	bid=bet;
printf("new bid is %d \n",bid);
 sprintf(buf,"%d",bid);
	n= sendto(sock,buf,20,0,(struct sockaddr *)&from,fromlen);

}else{n= sendto(sock,"the same",20,0,(struct sockaddr *)&from,fromlen);
}
	if (n < 0)
	{
		error("sendto");
	}
}
}

int main(int argc, char *argv[])
{



if (argc< 2)
{
	fprintf(stderr,"Error,no port provided\n");
	exit(0);
	}
sock=socket(AF_INET,SOCK_DGRAM, 0);
if (sock < 0 )
{
	error("opening socket");
}
length= sizeof(server);
bzero(&server,length);
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(atoi(argv[1]));
if (bind(sock,(struct sockaddr *)&server,length)<0)
{
	error("binding");
}
fromlen= sizeof(struct sockaddr_in);

pthread_t tid;

pthread_create(&tid,NULL,serv_h,NULL);
pthread_join(tid,NULL);
}

