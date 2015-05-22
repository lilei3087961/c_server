//============================================================================
// Name        : server.cpp
// Author      : westchou
// Version     : 1.0.0
// Copyright   : Your copyright notice
// Description : Created on 2015-5-19
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <pthread.h>
#include <sched.h>

#define SERVER_PORT		8000
#define BACK_LOG 		20
#define BUFFER_SIZE 	1024

void* RecvProc(void* pThreadParameter)
{
    int fdSocket = *(int*)pThreadParameter;

	while(1)
	{
        char buffer[BUFFER_SIZE] = {'\0'};
        int length = 0;
        if (-1 == (length = recv(fdSocket,buffer,BUFFER_SIZE,0)))
        {
            printf("Server Receive Data Failed[%d]!\n",fdSocket);
            break;
        }

		static int i  = 0;
		++i;
		buffer[length] = 0;
		printf("received data[%d] is : %s\n ",i, buffer);
		char message[] ="this is server in thread lilei";
		send(fdSocket,message,sizeof(message),0);     //发送类信息
	}

	return NULL;
}

int main(int argc, char **argv)
{
  	printf("Linux Server Main\n");

    int server_fd = 0;
    if(-1 == (server_fd = socket(PF_INET,SOCK_STREAM,0))){
        printf("Create Socket Failed!\n");
        exit(1);
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    if(-1 == bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))){
        printf("Server Bind Port : %d Failed!\n", SERVER_PORT);
        exit(1);
    }

    if(-1 == listen(server_fd, BACK_LOG))
    {
        printf("Server Listen Failed!\n");
        exit(1);
    }

    int client_fd = 0;
    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t sin_size = sizeof(struct sockaddr_in);
        bzero(&client_addr,sin_size);
		if(-1 == (client_fd = accept(server_fd,(struct sockaddr*)&client_addr,&sin_size)))
		{
			printf("Server Accept Failed!\n");
			continue;
		}

		printf("received a connection from [%s,%d]\n", inet_ntoa(client_addr.sin_addr),client_fd);

		pthread_t		thread;
		pthread_attr_t 	attr;
		pthread_attr_init(&attr);
		pthread_attr_setschedpolicy(&attr, SCHED_RR);
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
		pthread_create(&thread, NULL, RecvProc, &client_fd);
        //RecvProc(&client_fd); //for test by lilei
		char message[] ="this is server";
		send(client_fd,message,sizeof(message),0);     //发送类信息
    }

    close(server_fd);

    return 0;
}
