 
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
pthread_t thread[2]; //¿¿¿¿¿¿¿¿¿¿
pthread_mutex_t mut; //¿¿¿¿¿
int sid = -1;
int twoWay =1;  //whether in two-way long connect mode
void clientSend(int count){
  if(sid == -1){
     printf(">>clientSend()~~ ~~sid == -1  \n");
     sid = createSocket();
  }
  char newStr[] ="adam";
  printf(">>clientSend(%d) send() sid is:%d \n",count,sid);
  send(sid,newStr,strlen(newStr)*sizeof(char),0); //no close 
}
void clientSendThread(){
    // clientSend();
    //pthread_create(&thread[0], NULL,clientSend, NULL);	  
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
    int sendCount = 0;
    while (1) //
    {
        //
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);
        printf("main() tid=%d, pid=%d \n", syscall(SYS_gettid), getpid()); 
        printf("wait for connecting...\n");
        int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        printf("~~~get a connection! \n");
        if ( new_server_socket < 0)
        {
            printf("Server Accept Failed!\n");
            break;
        }
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        //add for by lilei begin
        char byteCharsAll[BUFFER_SIZE];
        bzero(byteCharsAll,BUFFER_SIZE);
        int lenAll = 0;
        short read = 1;
        int countRecv = 1;
	while(twoWay)
 	{
	   printf(">>>> recv() %d begin \n",countRecv);
           length = recv(new_server_socket,buffer,BUFFER_SIZE,0);
           if(length < BUFFER_LIMIT){
             read = 0;
             
           }else{
             read = 1;      //reset flag read
           }
           printf(">>>>get a new recv() length:%d,is need next recv():%d \n",length,read);
           if (length <= 0)
           {
             printf("Server Recieve Data Failed!\n");
             break;
           }else
	   {
             printf(">>>>received data length is: %d size char is:%ld \n", length,sizeof(char));
	          
             //writePngFile(buffer,length);
	     char byteChars[length+1];  //for save chars without NULL
             bzero(byteChars,length+1); //clear every char to zero
             int i = 0,len = 0; 
             char null = NULL;
             for(i; i < length; i++){
                if(buffer[i] != null){
		  byteChars[len] = buffer[i];//only save none null ascii char
		  len++;
		}
                //printf(">>>data is %d>>is not ascii zero:%d\n", buffer[i],(buffer[i] != null));
	     }
             const char END_CHAR = '\0'; 
             if(read == 0 && countRecv ==1){ //parse,only recv() one time
               byteChars[len] = END_CHAR;    
               testJson(byteChars,len);
               countRecv = 1;  //reset flag countRecv
               lenAll = 0;
             }else{  //shoul recv more than one time
               int i,j;
               for(j=lenAll;j<lenAll+len;j++){
	         byteCharsAll[j] = byteChars[j-lenAll];
               }
	       lenAll += len;
               if(read ==0){
		 byteCharsAll[lenAll] = END_CHAR;
                 testJson(byteCharsAll,lenAll);
                 countRecv = 1;
                 lenAll = 0;
	       }else{
                 countRecv++;  //increase flag 
               }
             }
           }
           //printf(">>>> recv() %d end \n",countRecv);   
           //countRecv++;
        }
        printf(">>>>>all recv() end 222 sendCount:%d \n",sendCount);   
        if(sendCount < 2){
           sendCount++; 
     	   //char jsonStr[] = "adam";
    	   //send(new_server_socket,jsonStr,sizeof(jsonStr),0);       //¿¿¿¿
    	   //printf("<<no close new_server_socket  begin send size:%ld json str:%s >>sendCount:%d\n",sizeof(jsonStr),jsonStr,sendCount); //*/
	   //clientSend(sendCount); //
        }
        close(new_server_socket);
        
    }
    close(server_socket);
    return 0;
}
