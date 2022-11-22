#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  int w,h;
 struct ppm_pixel* read = read_ppm(argv[1],&w,&h);
 printf("Reading %s with width %d and height %d\n",argv[1],w,h);//not able to get w and h
 unsigned int* listofnum = malloc(sizeof(unsigned int)*30000000);
 int count =0;
 for(int i =0; i<h;i++){
   for(int j=0;j<w;j++){
     if(read[i*(w) + j].red%2==0){//when num is even put 0
       listofnum[count]=0;
       count++;
     }else{//when num is odd put 1
       listofnum[count]=1;
       count++;
     }
     if(read[i*(w) + j].green%2==0){//when num is even put 0
       listofnum[count]=0;
       count++;
     }else{//when num is odd put 1
       listofnum[count]=1;
       count++;
     }
     if(read[i*(w) + j].blue%2==0){//when num is even put 0
       listofnum[count]=0;
       count++;
     }else{//when num is odd put 1
       listofnum[count]=1;
       count++;
     }
   }
 }
unsigned char* decode = malloc(sizeof(unsigned char)*10000000);
 int x=0;
 for(int i =0;i<count;i+=8){
   char sum=0;
   sum+=listofnum[i]*pow(2,7);
   sum+=listofnum[i+1]*pow(2,6);
   sum+=listofnum[i+2]*pow(2,5);
   sum+=listofnum[i+3]*pow(2,4);
   sum+=listofnum[i+4]*pow(2,3);
   sum+=listofnum[i+5]*pow(2,2);
   sum+=listofnum[i+6]*pow(2,1);
   sum+=listofnum[i+7]*pow(2,0);
   decode[x]=sum;
   x++;
 }
 printf("Max number of characters in the image: %d\n",x);
 for(int i =0; i<x;i++){
  if(decode[i]!=0){
   printf("%c",decode[i]);
  }else{
    break;
  }
 }
 unsigned char* encodeCh = malloc(sizeof(unsigned char)*10000000);
 unsigned int* encodeBinaray = malloc(sizeof(unsigned int)*10000000);
 printf("Enter a pharse:");
 scanf("%[^\n]s\n",encodeCh);
  int countbinar =0;
  for(int i =0;i<count;i++){
   int encodeInt = (int)encodeCh[i]+0;
   for(int j =0;encodeInt>0;j++){    
      encodeBinaray[countbinar]=encodeInt%2;    
      encodeInt=encodeInt/2;
      countbinar++;
    } 
 }
  struct ppm_pixel* encode = malloc(sizeof(struct ppm_pixel)*10000000);
  int countencode =0;
  for(int a=0;a<h;a++){
    for(int b=0;b<w;b++){
      encode[a*w+b].red = encodeBinaray[countencode];
      encode[a*w+b].green = encodeBinaray[countencode+1];
      encode[a*w+b].blue = encodeBinaray[countencode+2];
      countencode+=3;
    }
  }
  write_ppm("feep-raw-encoded.ppm", encode, 4, 4);
  printf("Writing file feep-raw-encoded.ppm\n");
 free(read);
 free(decode);
 free(listofnum);
 free(encode);
 free(encodeCh);
 free(encodeBinaray);
}
