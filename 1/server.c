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

int main(int argc, char *argv[])
{
    int listenfd = 0;
    unsigned int sent,connfd = 0;

    struct sockaddr_in serv_addr,client_addr; 
    int len = sizeof(client_addr);

    char sendBuff[1025];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(&client_addr, '0', sizeof(client_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    char *mesg = "Welcome to Venom's scoket!";

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)&client_addr, &len); 

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff));

	sent = send(connfd, mesg, strlen(mesg), 0);	 

	printf("Sent %d bytes to the client %s\n", sent, inet_ntoa(client_addr.sin_addr));

        close(connfd);
        sleep(1);
     }
}
