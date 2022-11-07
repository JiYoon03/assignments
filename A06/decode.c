#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "read_ppm.h"



int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }
  int w,h;
  struct ppm_pixel* pixels = read_ppm(argv[1], &w, &h);
  printf("Reading %s with width %d and height %d\n",argv[1],w,h);
  for (int r = 0; r < h; r++) {
    for (int c = 0; c < w; c++) {
       struct ppm_pixel p = pixels[r*w+c]; 
       printf("(%d,%d,%d) ", p.red, p.green, p.blue); 
    }
    printf("\n");
  }
 struct ppm_pixel* read = read_ppm(argv[1],&w,&h);
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
 for(int i =0; i<count;i++){
     printf("listofnum: %d\n",listofnum[i]);
  }
unsigned char* decode = malloc(sizeof(unsigned char)*10000000);
 int x=0;
 for(int i =0; i<count;i+=8){
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
   printf("decode: %c\n",decode[i]);
   printf("%02X\n", decode[i]);

 }
 free(read);
 free(decode);
 free(listofnum);
}
 

