#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

#define MAX_DATA 1024

int main(int argc, char *argv[])
{
    int listenfd = 0;
    unsigned int sent,connfd = 0;

    char data[MAX_DATA];
    int data_len; 

    struct sockaddr_in serv_addr,client_addr; 
    int len = sizeof(client_addr);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(&client_addr, '0', sizeof(client_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)&client_addr, &len); 
	
	printf("Sent %d bytes to the client %s:%d\n", sent, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

	data_len = 1;
	while(data_len)
	{
		data_len = recv(connfd,data,MAX_DATA,0);
		
		if(data_len)
		{
			send(connfd,data,data_len,0);
			data[data_len] = '\0';
			printf("Sent mesg: %s\n",data);
		}
	} 

	printf("Client disconnected!");	

        close(connfd);
        sleep(1);
     }
}
