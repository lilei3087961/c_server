//============================================================================
// Name        : clinet.cpp
// Author      : westchou
// Version     : 1.0.0
// Copyright   : Your copyright notice
// Description : Created on 2015-5-19
//============================================================================

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>
#include <sched.h>

#define BUFFER_SIZE 	1024
#define SERV_PORT 8000

void* RecvProc(void* pThreadParameter)
{
    int fdSocket = *(int*)pThreadParameter;

	while(1)
	{
        char buffer[BUFFER_SIZE] = {'\0'};
        int length = 0;;
        printf(">>>received before recv 111 \n");
        if (-1 == (length = recv(fdSocket,buffer,BUFFER_SIZE,0)))
        {
            printf("Client Receive Data Failed!\n");
            break;
        }
            printf(">>>received after recv 222 length is:%d\n",length); 
		static int i  = 0;
		++i;
		buffer[length] = 0;
		printf("received data[%d] is : %s\n ",i, buffer);
	}

	return NULL;
}

int main(int argc, char **argv)
{
	struct hostent *nlp_host = NULL;
	char host_name[] = "localhost";
	if(NULL == (nlp_host=gethostbyname(host_name))){
		printf("gethostbyname(%s) error\n",host_name);
		exit(1);
	}

	int sockfd = 0;
	if(-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0))){
		printf("socket create error！\n");
		exit(1);
	}

	struct sockaddr_in serv_addr;
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;                 //AF_INET use IPv4
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_addr.s_addr = ((struct in_addr *)(nlp_host->h_addr))->s_addr;
	serv_addr.sin_port = htons(SERV_PORT);


	if(-1 == connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))){
		printf("Connect Error!\n");
		exit(1);
	}

	pthread_t		thread;
	pthread_attr_t 	attr;
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_create(&thread, NULL, RecvProc, &sockfd);
	//RecvProc(&sockfd); //for test

	char message[] ="this is client";
        int len = strlen(message);
        message[0] = 0x00;
        message[len-1] = 0xff;
	for(int i = 0;i < 6;++i)
	{
          send(sockfd,message,sizeof(message),0);
	  printf("[client] send class size: %ld\n",sizeof(message));

	  sleep(3);
	}

	pause();

//	close(sockfd);

	return 0;
}
