 
//gcc -o hello hello.c 

#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero
#include <netdb.h>
#include <pthread.h>      //for thread
#include <sys/syscall.h>  //for ?
//for local .h
#include "util/byteMap.h"

#define HELLO_WORLD_SERVER_PORT    8001
#define HELLO_WORLD_CLIENT_PORT    4700
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 30000
#define BUFFER_LIMIT 1448 
#define FILE_NAME_MAX_SIZE 512
pthread_mutex_t mut; //�����
int sid = -1;
const char ADD_BEGIN_END_CHAR = 0;
const char READ_BEGIN = 0xff;
const char READ_END = 0xfe;
const char END_CHAR = '\0';  
//*/
//int twoWay =1;  //whether in two-way long connect mode
void * RecvSocket(void * fd){
  int fdSocket = *(int*)fd;
  printf(">>>>RecvSocket() begin fdSocket is: %d  \n",fdSocket);
  char buffer[BUFFER_SIZE];
  bzero(buffer, BUFFER_SIZE);
  //add for by lilei begin
  char byteCharsMsg[BUFFER_SIZE]; //to store one messgage
  bzero(byteCharsMsg,BUFFER_SIZE);
  int lenAll = 0;
  int index = -1;  //byteCharsMsg index
  short read = 1;  //judge wthether > BUFFER_LIMIT
  short readBegin = 0;  //judge wthether find byte READ_BEGIN
  short readEnd = 0;
  int countRecv = 1;
  int length = -1;
  int sendCount = 0;
  while(1)
  {
    printf(">>>> recv() %d begin \n",countRecv);
    length = recv(fdSocket,buffer,BUFFER_SIZE,0);
    if(length < BUFFER_LIMIT){
      read = 0;
    }else{
      read = 1;      //reset flag read
    }
    printf(">>>>get a new recv() length:%d,is need next recv():%d \n",length,read);
    if (length <= 0){
      printf("Server Recieve Data Failed!\n");
      break;
    }else{
      printf(">>>>received data length is: %d \n", length);
      char null = NULL;
      int i = 0,len = 0;
      if(!ADD_BEGIN_END_CHAR){  //for short message
    	  index = -1;
    	  for(i=0; i < length; i++){
    		  if(buffer[i] != null){
    			  byteCharsMsg[++index] = buffer[i];
    		  }
    	  }
    	  len = index + 1;
    	  testJson(byteCharsMsg,len,fd);
    	  return 0;
      }

      if(!readBegin)
	    index = -1;
      for(i; i < length; i++){
	//printf(">>>data is %d>>is not ascii zero:%d\n", buffer[i],(buffer[i] != null));
        if(READ_BEGIN == buffer[i]){
          printf(">>>>received byte READ_BEGIN~~~~~~~~~\n");
          readBegin = 1;
          readEnd = 0;
        }else if(READ_END == buffer[i]){
          printf(">>>>received byte READ_END~~~~~~~~~\n");
          readBegin = 0;
          readEnd =1;          
        }

        if(readBegin && READ_BEGIN != buffer[i] && buffer[i] != null){
          byteCharsMsg[++index] = buffer[i];   
        }else if(readEnd){
          len = index + 1;
          index = -1;  //reset index to -1
          byteCharsMsg[len] = END_CHAR;
          testJson(byteCharsMsg,len,fd);
        }      
      }
    
      if(read ==0){
        countRecv = 1;
      }else{
	countRecv++;  //increase flag 
      }
    }
    //printf(">>>> recv() %d end \n",countRecv);   
    //countRecv++;
  }
  printf(">>>>>all recv() end 222  \n");   
  //close(fdSocket);//may close 
}
void RecvScoketThread(int * send_fd){
    // clientSend();
    pthread_t thread; //
    pthread_create(&thread, NULL,RecvSocket, send_fd);	  
}
int main(int argc, char **argv)
{
    printf("main~~ \n");
    test1();
    //for sersocket begin
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr)); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
	 
    printf("main~~~~init server scoket\n");
    //create socket server_socket
    int server_socket = socket(PF_INET,SOCK_STREAM,0);
    if( server_socket < 0){
        printf("Create Socket Failed! \n");
        exit(1);
    }
    {
        int opt =1;
        setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    }
     
    //bind socket
    if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("Server Bind Port : %d Failed! \n", HELLO_WORLD_SERVER_PORT);
        exit(1);
    }
 
    //listen socket
    if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
    {
        printf("Server Listen Failed!\n");
        exit(1);
    }
    while (1) //
    {
        //
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);
        printf("main() tid=%d, pid=%d \n", syscall(SYS_gettid), getpid()); 
        printf("wait for connecting...\n");
        int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        printf("~~~get a connection! new_server_socket is:%d \n",new_server_socket);
        if ( new_server_socket < 0)
        {
            printf("Server Accept Failed!\n");
            break;
        }
        RecvScoketThread(&new_server_socket);  
        
    }
    close(server_socket);
    return 0;
}
