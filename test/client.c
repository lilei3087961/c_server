#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int sd = -1;

int createSocket()
{
  printf("createSocket()~~ \n");
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
  printf("createSocket() 111 connecting:%s port:%d\n",host_name,port);
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
  return sd;
 /* char jsonStr[] = "client";
  send(sd,jsonStr,sizeof(jsonStr),0);       //发送数据
  close(sd);
  printf("sendJson() json size:%ld json str:%s\n",sizeof(jsonStr),jsonStr);
  printf("2222 end~~~\n");//*/
}

void test(){
    char *t = "百度手机助手"; 
    char *enc="iVBORw0KGgoAAAANSUhEUgAAAGAAAABgCAYAAADimHc4AAAABHNCSVQICAgIfAhkiAAAEKZJREFUeJztnXl4k1W+xz\/vmzdrkzQtXSitlbJ02HdBBJXlPgyDdUERBe44blfvRUd9nLHI6Mz0Ovo4AndQUcFlfFCvDuLIqIM41lvZBAexiAXKUitLCy3d0qZJkyZ5894\/AqUlKbRN0sQxn+fp8\/Q557znnPd8z\/o77zkR6CKbh79obB7APK1Kfb3eJY2UHEKq4FE0oiAICCCoWhk68I9dje6CeNU6H1NA8rnEsEQI\/Pfw8MQj+XS+Dw5\/icsniQrgA0WD123GWZvgbd7na3V+VCaOfq\/2PsHepfguFuCdBc+mp7QkvKqrl2YZ93m0fldvQDiVqhVj0rFuvUxnKAYz+EDw2MISH4BNFZ54dGozp3yJ2DxCB2ewmCFjIBpuGKCxrR708pHCpKaT92zKn159ofg6rWGKogif3PDq2oHliSeTvlWulSrPFn7kERAQBOHiAaOAIFw8b9+7zdovGXzttykTK698+eBaRVE6fSCoAOtvXpXzxey1lSl7lV+INZ4w1Z0fHyc9BtV2hvxi3NrTFbOWb80JFiZAgA15L0zOPpFQqjvs6Rf5LP44+MadnlmaPL506rNfTzrfr4MA6+auHNrvtGGL6rRX13vZ+3FQ6U3QVZpzt167\/KMOLaFtEF6\/fr2q3xrHVlWtR9P72bsAmkRInwypEyBpOJhyICETNBZQG\/1hPHZwN4LjFDR\/D9YDUPs1nP4S3E3RzX87jnlM2j4pE3euX78+a\/78+TK0E8DyZtPftN8rqdHLXjuS+8HwGyF7DqRNAuEiw5Da6P9LyIK0iefcFRlqdsHRDSRr3qPBfSKy+e4Cxe70vn\/yjNsAXA8gAHw0+9nL+p4w7hJafD2eeqhUTsYOfzC03A2\/CuY+AuN\/BmJ4x36fIrPf9gmfnV7BkeatPY5Hr0pk7d5Gmtw9z0uC6FWGOg9c\/vUDY76SABIk03NCixy9ed+IabDoCRh2ZcSSEAUVoxLzGJWYR5l9Ox+d+h1HmrdELL0L4fBJgspgeQ6YLHx82Yt9U9y6k2KTHNKqs0ctICkD7lgOVy8KJekes6vhbd6vfIQmT1WXnwlHCwBIVrX60pursyRfpuo+cW9ohd8jptwM978KhsQuBZftJ3Gf\/BJvwyFk2wkUVyM+t3+lLGrMCDoLKnM2UvIQNJmTURkzLxrnpORFjErM463j\/0Gx9b2QXqe7NMhacZjetlhK8KjngNx7KUsauPN\/4Jr7LxrUU7WbltL\/pfXop3gbDncvmeRctDmz0Q9bhCZjYqfh9KpE7hmwns01L\/DXyl\/jVVq7lU4otKoT50hauzig1wTQm2Dp32D0zE6DKF43zs\/fxl79Et7qr9vcVSJoJJBE\/\/+CAOKZUcungKKA7AOvD9xe8DYcwdtwBEfx80h9hnJg1kNcmXk7khh8lj097X6yDKNYXT4Xh7chrK\/dGU2CaYAotSimXkktMRWe2nzBwnd98T41d+TS+NKDeBsOo1ZBoh7SzJBuhiQDmHRg0IBeDVrJ\/6dX+91MOn+YdLP\/mUS9XzRv\/UFeP3Avj2zPZffp9ztNf7DxKh7O\/RyT1Duz8WZFZxIFpxL5\/t+QCL\/\/BwwcH9RbrjtJ\/eNzaPjDPHw1xzGoBNLMIqkmSND6a313kUT\/sylGvxiSDupcx3n+m3msKJ6DtfVU0Oey9KN5cPCn6FVdG5tCoUWRRBG5c0tdWJA0sHQDDBwX1Lu1uJDaxWNp3f0JOhHStGDRCD0q9E6zIILGBPpkUGnh29pPeGzHGPbVFQYNf4lhLP85cAOSEFmjgEcRhMjX\/rtWwqgZQb1aNr1C\/eNzEGy19NFAsgZUEawOgghaM2gTwS7XsqJ4DpsrXgkadohpBjdfsjJymcG\/Co6sAFNuhjmLg3rZ31tO43P3okUmVQPaXpwIqzSgswBqmdcP3MvHR5cHDTctdTETkuZHNC+Re+0+mXBf8Nrl2Lga22v5GFTQR3NuNtObCCLoEv1jw7rD+RSdWB003KJLXyZJkxWxfEROgHtWQYIlwLm1uJCmF3+JUQKLOmKpdxmNCSQDvHnwl0HHBIPKwi2XPB+x9CMjwMjpcPncAGe5oQrrsp+TIMiYL7ob3XtoEkDUyawp+XnQ2dFYy1yGmDqfPodCZARY+ERQ58YVt6O21ZAYAzX\/fDRGsFPDq\/vuCOp\/bb+CiKQbfgGGXwXDpgY4O7esw7unkKQYLPyzaE2w31rIzqp3AvwGGacy2HhV2NMMvwBzHwlwUrxubK8vxaKOzoDbVQTR3xLeO\/IbvL5Ac+esvoHvFirhFSAxDcbNDnB2fvYGmrpjvTrV7CkqDVh9x9l+8o0AvxHm2RjDbKYIb5FcvRBUgaOrY8OzMTXoXgyNEf5xPHARJgoS45PmhTUtYfPmzcq0adPCGml7PB4PDocDiyVwSmrJ\/y5i6XaVLIvE\/t\/0D3BvbGzEYDCg0UTOHLFly5YIr4SBlpYWjEZjpJMJO0ajEafTGfF0Ii6ALMtI0g+o\/zmDJEn4fL6IpxM2ARRFCXCTZRmtttc+KQ07Go0GWQ7crAr2rj0lbAIEy6jH4wmrAHdNTqTiiQGU\/S6HmbmGAP8rB+r56dCEsE11tVotbnfgdDTYu\/aUsAhQV1eH1WoNcK+vrw9b9zMqU8vyG1Ix6URSjSrevj2DTIs\/blGAVxek8\/d7M3n3jgzW3dEPKQwqSJJEfX19gLvVaqWuri7k+CEMAni9XgoLC9Hr9QF+Bw8epLa2NtQkAFgwztShZuskgVvG+ndT77vKws1jz+2szhpi4PZJ5pDTrK+v59ChQwHuer2eTz\/9FK838JxEdwlZgGPHjmG324N2NR6Ph4MHD4aaBAA5fQJtGJcmq1GJ8KsZyQF+M38S2EV1lwMHDuDxeALcNRoNDoeDo0ePhpxGyP2Dzeb\/NketDiwgt9sdlloC0OgKnJE0uWTMOhUWfWA9cnpCHyhtNlvQ\/v7s2qCpKfQPf0NuAWe7nvO7Gp\/PR0NDAwZDz2ri6EwtC8ab6HtmCb2lrCUgzOdHnNhcMm45sLA3fNvco3TbYzAYaGhoCJiOnu3\/e\/pu7QlZgJycHNRqNZ999lnbwkWWZYqKinA6nQwePLjbcd420cyWBy5h9S3p7MnP5t9+YuCv39jZddzVFmb9N81sKWtB9sH6PR0Le+N+Bxv3O0J7MSA3Nxen00lRUVFbS3A4HBQWFqJWq8nJCXropVuE3AXpdDqmTZvGhx9+yJo1a0hLS8NqtdLS0sKUKVPIzs7uVnxaSeAP16Rw9hiWQSPyyoJ0hj11jBteOcmNo024vD4+KDl3CPGh92vZfcLFmEwtJafcvPWVjdnDErh7ciIqEdYVN\/Punu63iKysLMaMGcOOHTs4cuQISUlJ1NTUAHDdddcFnXh0l7DMEXNycli4cCG7du2iqamJjIwMRo4cSW5ubrfjury\/jsTz+vRkg4qJl+rY9p2Tt78OPDnp9Sm8scvGWfvlqEwtb9+WgepMNNMHG1CJAu8EefZiXHHFFaSkpLBv3z6cTicDBw5k4sSJpKendzuuYITNRpCWlkZeXh4ejwdJkhDFnvVuSYbg5wLU583r1SqB7CSJhhYf1paOA+XcUca2wj\/LA1dbeiQA+LuiQYMG4fV6UavVYT3BGVYjjSAIIVsPD1YH\/+77hNV7Jg2470oLD89IItmgwqfAhyV2HtpQQ5PTP1hmWQJfa3BqaPkSRTEiltGY2yI5XOOm8FDHGc+WshbKav3CPDarD0\/mpZB8pqWIAswdbeT9u\/qhOfNVlxzEhub0RN6w1hNiTgCAu9+pZs0XjWz7zsnKzVb+\/U3\/YfMZuQZ+NSMp6DMTsnWsvMm\/W1VyKvAT8\/1VIZ6oiBAxaSe2uXw8+lFHW8vwDA1\/XpiOIEBptZtXdjTywLQkBrRbIS+aYGZ\/lZt1xc3cNtHMkHR\/l+HyKDxdGGjTiQViUoDzuSxbx7t3ZrQN0BVWD2t32bh1vLmDAABP5aXQ7PIxdWUFE7K1WPQqiitc1Np78RBKN4h5AeaPNfH8vDR06q7NPEQBVs1LQycJvPZl7JwR7oyYFuCxnybzyEy\/oW3V1kY2fNuMAtic5wbUxzfWcXl\/PXkjEjjdLLN6eyM3jTGyYm4q2ckSv99UTxj3T8JOTA7CANeOMLYV\/l+Km\/ntx3UMz9Dy0LQkrh91bo\/5hW2NFFf4TRT1Dplnt1g5dNo\/4D5wdVJbHLFKzLaAOyefs+e\/+ZWNAX3UrJqXhiCAvovdEcDD05N4aXsj9tb4NLRb9E8+N7gqioJBI9KTBahOLTCyX+zuS8esAFVN5\/YR5o8zsb+qld9+XMcHJXb+eeycVVSvFth13MUHJXY+PxJosgbwBjFXxwox2wV9XOrgigF+a+OdlyciCgJvfWXj7\/v8Zub+yWq0ksDKm9JYtdVKwab6Nndju28gW9w+9lX13tnf7hKzAvx5ZxOLJpgZ1te\/mLp9kjnoPu\/YLC23juv8pO3r\/7ThCsPuWKSIWQFcXoVr1pzk1zOSmJFrQK8RkH3+rum7Og9HatzUO2QSdSL9LBKX99czNkuLVvIPFDV2mTd32Xjm\/3rn0HVPiVkBAKwtMo9t7PrnH5IokGwQUfBPSX2xW\/HbiKoAyQYVDS3hMxF4fQo13TQ5dLb\/0FtEdRZ06\/jeuSXhQiyIch6i2gIK5vRBFPwr3XpH7xrL+pol7p6cyH9NDfxsvjeJqgAalcCTeSk8mZcSzWxElZhdiP1YiAsQZeICRJm4AFEmLkCUiQsQZeICRJm4AFEmLkCUiQsQZeICRJm4AFEmLkCUiQsQZeICRJm4AFEmLkCUiQsQZeICRJm4AFFGVBTF3RtXc8XpiM\/nQ1EUt+j1em3hvAEqTteQZRmv12sTXS5XeW\/cDhinI06nE5fLVS7a7fYShyP0m0XidA+Hw4Hdbi8RrVZrUbD73uJEFqvVitVqLRLtdvum6upqR3wc6D1kWaa6urrFbrdvEpcsWdJcU1Ozrqqq67+nGCc0qqqqqKmp+cuSJUuaRYBjx479sayszBNvBZFHlmXKyso8FRUVzwCoAIqKihpmzpxpNJlMU5KTY\/tc7Q+do0ePUlpa+qfFixe\/C+1WwnV1dQWHDx8uqaysjF7u\/sWprKzk8OHDJeXl5QVn3TqcvH366acHjR8\/fueIESNSMzIyIpKJ5jUvYVuxDCVMa48Ri3aEJR6jVuTBaZaInayvqqpi\/\/79tcXFxVcsXbq07d7+DudzioqKGkaOHFkkiuINWq3WaDaHfvtse+SqU9TdtgiCXIbaU14adVdY4nHLCl987+TG0Ub6JIT32FJlZSWlpaWn9+7d+7NHH330QHu\/AGNcfn7+nuLi4qklJSUl5eXlYb2o2tfUBDFsd1IUaGgJX\/5kWaa8vJySkpKS4uLiqfn5+XvODxPUGrp06dLvdu\/ePWnnzp3Ltm3b5qmsrAyrEP\/q+Hw+Kisr2bZtm2fnzp3Ldu\/ePal9t9OeTo8oFRQUuIAly5Yte626ujo\/PT19Yd++fQ0WiwWj0Yher0eSpLDeIPhDRFEUvF4vTqcTu91OY2Mj1dXVzpqamncqKiqeyc\/PL7vQ810uvYKCAmN6enqexWKZnpCQMEan0+VIkmQRBKHLvwymqThB9qPh\/SmocA3CZ3l6ci1Dk7p+tYGiKB6v19vocrmOOhyOvY2NjZtPnz69saCgwH7xp+H\/AX7L3FieFxnVAAAAAElFTkSuQmCC";
    /*int i = 0; 
    int j = strlen(t); 
    char *enc = base64_encode(t, j);
    */
    int len = strlen(enc);
    int lenDec = -1;
    char * dec = base64_decode(enc, len,&lenDec); 
    //printf("\noriginal: %s\n", t); 
    printf("\nencoded : %s\n", enc); 
    printf("\ndecoded len is:%d>>encoded len is:%d\n", lenDec,len); 
    //printf("\ndecoded dec2 : %s\n", dec2); 
    char path[256] = "11.png";
    FILE * file;
    file = fopen(path,"ab+");
    fwrite(dec,lenDec,1,file);
    fclose(file);  //*/

    }
char * tt(int * count){ //call tt(&a) to return count
    char * str; 
    char * s; 
    str = (char *)malloc(10);
    s  = (char *)malloc(10);
    s = str;
    *str = 'a';
    str++;
    *str = 'b';
    str++;
    *str = 'c';
    str++;   
    *str ='\0';
    *count = 10;
   printf(">>tt()>>str is:%s>>s is:%s \n",str,s);
  return s; 
}
int main(){
   printf(">>main  ## \n");
   test();
}
