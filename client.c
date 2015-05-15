#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

long getNowMills(){
    struct timeval time;
    gettimeofday(&time,NULL);
    long mills =  (1000000*time.tv_sec+time.tv_usec)/1000;   
    //printf("now mills: %ld \n",mills);
    return mills;
}
int main()
{
  void sendJson(int sd);
  printf("test clent~~ \n");
  struct sockaddr_in pin;
  struct hostent *nlp_host;
  int sd; 
  char host_name[256];
  int port;
  char newLine[1] = "\n";
  char msgState[] = "100";
  strcat(msgState,newLine);    //添加换行符
  char packageNmae[] = "com.android.browser";
  strcat(packageNmae,newLine); //添加换行符  
  char className[] ="com.android.browser.BrowserActivity"; 

  //getOneApp(msgState,className); //手机wifi ip 192.168.31.81
  //初始化主机名和端口。主机名可以是IP，也可以是可被解析的名称localhost
  //strcpy(host_name,"localhost");
  strcpy(host_name,"192.168.31.81");
  port=4700;
 
  //解析域名，如果是IP则不用解析，如果出错，显示错误信息
  while((nlp_host=gethostbyname(host_name))==0){
    printf("Resolve Error!\n");
  }
  printf("1111 connecting:%s port:%d\n",host_name,port);
  //设置pin变量，包括协议、地址、端口等，此段可直接复制到自己的程序中
  bzero(&pin,sizeof(pin));
  pin.sin_family=AF_INET;                 //AF_INET表示使用IPv4
  pin.sin_addr.s_addr=htonl(INADDR_ANY);  
  pin.sin_addr.s_addr=((struct in_addr *)(nlp_host->h_addr))->s_addr;
  pin.sin_port=htons(port);
 
  //建立socket
  sd=socket(AF_INET,SOCK_STREAM,0);
 
  //建立连接
  if(connect(sd,(struct sockaddr*)&pin,sizeof(pin))==-1){
    printf("Connect Error!\n");
  } 
/*  send(sd,msgState,sizeof(msgState),0);       //发送configState
  send(sd,className,sizeof(className),0);     //发送类信息 */
  //getOneApp(sd);
  long timeBegin = getNowMills();
  long timeEnd;
  long timeDiff;
  int i;
  int count = 1;
  printf("send all app begin timeBegin:%ld \n",timeBegin);
  for(i=0;i<count;i++){
    printf("send i:%d \n",i);
    sd=socket(AF_INET,SOCK_STREAM,0);
    if(connect(sd,(struct sockaddr*)&pin,sizeof(pin))==-1){
      printf("Connect Error!\n");
    }     
    sendJson(sd); 
  }
  timeEnd = getNowMills();
  timeDiff = timeEnd - timeBegin;
  printf("send all app end timeEnd:%ld timeDiff:%ld \n",timeEnd,timeDiff); 
  printf("2222 end\n");
}
void sendJson(int sd){
  char msgState[] = "106";//111 start app
  char local[] = "zh_CN";
  char packageName[] = "com.android.settings";
  char className[] = "com.android.settings.Settings"; 
  char test[] ="{\":\"}:::{}}}{{{,,,,::""";
  char jsonStr[] ="{\"messageType\":104}"; //104 get all,111 start app,106 get one app
  char jsonStr2[]= "{\"messageType\":130,\"timeInMillis\":1420078210000}";
  char jsonStr3[] ="{\"messageType\":106,\"packageName\":\"com.android.contacts\",\"activityName\":\"com.android.contacts.activities.PeopleActivity\"}";
  char jsonStr4[] = "{\"messageType\":129,\"language\":\"zh\",\"area\":\"CN\"}";
  char jsonStr5[] = "abc";
  
  send(sd,jsonStr,sizeof(jsonStr),0);       //发送configState
 // send(sd,char2,sizeof(char2),0);
  printf("sendJson() json size:%ld json str:%s\n",sizeof(jsonStr),jsonStr);
}
void getOneApp(int sd){
  char newLine[1] = "\n";
  char msgState[] = "111";//111 start app
  char local[] = "zh_CN";
  char time[] = "1286676610000"; // 2010-10-10 10:10:10
  char packageName[] = "com.android.settings";
  char className[] = "com.android.settings.Settings"; 
  int lenP = sizeof(packageName);
  int lenC = sizeof(className);
  char arrLenP[3];  //若是两位数 必须是3，否则android端无法接收数据
  char arrLenC[3];
  sprintf(arrLenP,"%d",lenP);   //int 转换为String
  sprintf(arrLenC,"%d",lenC);

  strcat(msgState,newLine);  
  strcat(arrLenP,newLine);
  strcat(arrLenC,newLine);
  strcat(packageName,newLine);

  send(sd,msgState,sizeof(msgState),0);       //发送configState
//  send(sd,time,sizeof(time),0);      //设置时间
//  send(sd,local,sizeof(local),0);  //设置语言
  send(sd,arrLenP,sizeof(arrLenP),0);           //发送包长度
  send(sd,arrLenC,sizeof(arrLenC),0);           //发送包长度
  send(sd,packageName,sizeof(packageName),0);     //发送类信息
  send(sd,className,sizeof(className),0);     //发送类信息  */ 
  printf("getOneApp() state size:%ld arrLenP:%s arrLenC:%s \n",sizeof(msgState),arrLenP,arrLenC);
}
