 
//gcc -o hello hello.c 

#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero
#include "time.h"          //for time
/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
*/
#define HELLO_WORLD_SERVER_PORT    8001
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 30000
#define BUFFER_LIMIT 1448 
#define FILE_NAME_MAX_SIZE 512

 
long getNowMills(){
    struct timeval time;
    gettimeofday(&time,NULL);
    long mills =  (1000000*time.tv_sec+time.tv_usec)/1000;   
    //printf("now mills: %ld \n",mills);
    return mills;
}
void timediff(long start,long end){
    long timeuse = end - start;
    printf("time diff: %ld ms\n", timeuse);
}
int main(int argc, char **argv)
{
    //设置一个socket地址结构server_addr,代表服务器internet地址, 端口
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr)); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
    printf("main~~~~!time:%ld \n",getNowMills());
    //创建用于internet的流协议(TCP)socket,用server_socket代表服务器socket
    int server_socket = socket(PF_INET,SOCK_STREAM,0);
    if( server_socket < 0)
    {
        printf("Create Socket Failed! \n");
        exit(1);
    }
{
   int opt =1;
   setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
}
     
    //把socket和socket地址结构联系起来
    if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("Server Bind Port : %d Failed! \n", HELLO_WORLD_SERVER_PORT);
        exit(1);
    }
 
    //server_socket用于监听
    if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
    {
        printf("Server Listen Failed!\n");
        exit(1);
    }
    while (1) //服务器端要一直运行
    {
        //定义客户端的socket地址结构client_addr
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);
        printf("wait for connecting...\n");
        int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        long timeBegin = getNowMills();
        long timeEnd;
        long timeDiff;
        printf("connecting...timeBegin:%ld \n",timeBegin);
        if ( new_server_socket < 0)
        {
            printf("Server Accept Failed!\n");
            break;
        }
        short read = 1;
        char buffer[BUFFER_SIZE];
        char byteChar;
        bzero(buffer, BUFFER_SIZE);
        //add for by lilei begin
	while(read){
	   //printf(">>>> recv() 111 \n");
           length = recv(new_server_socket,buffer,BUFFER_SIZE,0);
           if(length < BUFFER_LIMIT)
             read = 0;
           //printf(">>>> recv() length:%d,read:%d \n",length,read);
           if (length < 0)
           {
             printf("Server Recieve Data Failed!\n");
             break;
           }else{
             //printf(">>>>received data is : %d\n ", length );
             int i = 0; 
             for(i; i < length; i++){
		byteChar = buffer[i];//test
             //printf(">>>data is %d\n", buffer[i]);
	     }
           }
           //printf(">>>> recv()222 ");   

        }
        timeEnd = getNowMills();
        timeDiff = timeEnd - timeBegin;
        printf(">>>> recv()222 timeEnd:%ld timeDiff:%ld \n",timeEnd,timeDiff);   
        //add by lilei end
        /*  if (length < 0)
        {
            printf("Server Recieve Data Failed!\n");
            break;
        }else{

           printf(">>>>received data is : %d\n ", length );
           int i = 0; 
           for(i; i < length; i++)
               printf(">>>data is %d\n", buffer[i]);
        }   */
        close(new_server_socket);
    }
    close(server_socket);
    return 0;
}
