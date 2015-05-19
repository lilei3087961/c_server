#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int clientSend()
{
  printf("test clent send~~ \n");
  struct sockaddr_in pin;
  struct hostent *nlp_host;
  int sd; 
  char host_name[256];
  int port;
  //getOneApp(msgState,className); //手机wifi ip 192.168.31.81
  //初始化主机名和端口。主机名可以是IP，也可以是可被解析的名称localhost
  strcpy(host_name,"localhost");
  //strcpy(host_name,"192.168.31.81");
  port=4700;
 
  //解析域名，如果是IP则不用解析，如果出错，显示错误信息
  if((nlp_host=gethostbyname(host_name))==0){
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
  char jsonStr[] = "client";
  send(sd,jsonStr,sizeof(jsonStr),0);       //发送数据
  printf("sendJson() json size:%ld json str:%s\n",sizeof(jsonStr),jsonStr);
  printf("2222 end\n");
}
unsigned char HexToChar(unsigned char bChar){
    if((bChar>=0x30)&&(bChar<=0x39))
        bChar -= 0x30;
    else if((bChar>=0x41)&&(bChar<=0x46))//大写字母
        bChar -= 0x37;
    else if((bChar>=0x61)&&(bChar<=0x66))//小写字母
        bChar -= 0x57;
    else bChar = 0xff;
    return bChar;
}
//dec ascii to char
unsigned char decToChar(char num){
   char out[2];
   sprintf(out,"%c",num);
   return out[0];
}
void test(){
   char a= 98;
   char b = decToChar(a);
   char * str ="拨号";
   int len = strlen(str);
   printf(">>main >>len is:%d>>str is:%s \n",len,str);
   int i;
   for(i=0;i<len;i++){
      printf(">>main>>str[%d] is:%d \n",i,str[i]);
   }
   
 printf("The bytes of the variables are:\n");
    printf("int:%ld bytes\n",sizeof(int));
    /* char型的字节数为1 */
    printf("char:%ld byte\n",sizeof(char));
    /* short型的字节数为2 */
    printf("short:%ld bytes\n",sizeof(short));
    /* long型的字节数为4 */
    printf("long:%ld bytes\n",sizeof(long));
    /* float型的字节数为4 */
    printf("float:%ld bytes\n",sizeof(float));
    /* double型的字节数为8 */
    printf("double:%ld bytes\n",sizeof(double));
}
int main(){
   printf(">>main \n");
   test();
}
