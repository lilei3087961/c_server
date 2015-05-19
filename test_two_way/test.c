#include "stdio.h"
#include "stdlib.h"

void bobSort(int a[],int len){
  int i,j,temp;
  for(i=0;i<len;i++){
    for(j=0;j<len-i-1;j++){
      if(a[j]>a[j+1]){
          temp = a[j];
          a[j] = a[j+1];
          a[j+1] = temp;
      }
    }
  }
}
void selSort(int a[],int len){
  int i,j,index,temp;
  for(i=0;i<len;i++){
    index = i;
    for(j=i+1;j<len;j++){
      if(a[j]<a[index]){
	index = j;
      }
    }
    if(i != index){
      temp = a[i];
      a[i] = a[index];
      a[index] = temp;
    }
  }
}
void insertSort(int a[],int len){
  int i,j,temp;
  for(i=1;i<len;i++){
    temp = a[i];
    for(j=i;j>0 && a[j-1]>temp;j--){
      a[j] = a[j-1];
    }
    a[j] = temp;
  }
}
main(){
  printf("main \n");
  int a[] = {6,3,7,9,1};
  int i,len = sizeof(a)/sizeof(int);
  printf("11 selsort len:%d \n",len);
  //bobSort(a,len);
  //selSort(a,len);
  insertSort(a,len);
  printf("22 len:%d \n",len);
  for(i=0;i<len;i++){
    printf("a[%d]=%d \n",i,a[i]);
  }

}
