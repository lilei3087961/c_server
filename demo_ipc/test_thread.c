    #include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Msg{
  int fd;
  char * jsonStr;
}JsonMsg;

void * sendHeartBeatMsg(void * jsonMsg){
  JsonMsg jMsg = *(JsonMsg *)jsonMsg;
  printf("sendHeartBeatMsg() >>fd is:%d >>jsonStr is %s \n",jMsg.fd,jMsg.jsonStr);
  while(1){
    printf("sendHeartBeatMsg() ~~\n");
    sleep(10);
  }
}
sendHeartBeatInstak(JsonMsg * jMsg){
  printf("sendHeartBeatInstak \n");
  pthread_t thread;
  pthread_create(&thread,NULL,sendHeartBeatMsg,jMsg);
  pthread_join(thread,NULL);
}

int main(void)
{
  int sd = 1;
  printf("file is:%s, function is:%s \n",__FILE__,__FUNCTION__);
  char arr[]="123"; 
  JsonMsg * msg = (JsonMsg *)malloc(sizeof(JsonMsg));
  msg->fd = 1;
  msg->jsonStr = arr;
  sendHeartBeatInstak(msg);
  //return(0);
 }
