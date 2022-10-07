#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  FILE *infile;
  if (argc != 2) {
    printf("usage: ascii_image <file.ppm>\n");
    return 0;
  }
  if (argc != 1) {
    printf("usage: ./ascii_image filename.c\n");
  }  
  infile = fopen(argv[1], "r");
  printf("Testing file %s:",infile);

  struct ppm_pixel* read = read_ppm(infile);

  int linenum=0;
  int w,h;
  while (fgets(pixels,3*w*h, fr) != EOF) {
    linenum++;
    if(linenum==3){
      w=pixels[0];
      h=pixels[2];
    }

  int* intensity = malloc(sizeof(int)* w * h);

  // compute the average intensity 
  for(int i =0; i<h;i++){
    for(int j=0;j<w;j++){
      intensity[i*w + j]=((read[i*w + j].red)+(read[i*w + j].green)+(read[i*w + j].blue))/3;
    }
  }
  for(int i =0; i<h;i++){
    for(int j=0;j<w;j++){
      if(0<=intensity[i*w + j]&&intensity[i*w + j]<26){
        printf("@");
      }else if(intensity[i*w + j]<51){
        printf("#");
      }else if(intensity[i*w + j]<76){
        printf("%c", '%');
      }else if(intensity[i*w + j]<101){
        printf("*");
      }else if(intensity[i*w + j]<126){
        printf("o");
      }else if(intensity[i*w + j]<151){
        printf(";");
      }else if(intensity[i*w + j]<176){
        printf(":");
      }else if(intensity[i*w + j]<201){
        printf(",");
      }else if(intensity[i*w + j]<226){
        printf(".");
      }else if(intensity[i*w + j]<256){
        printf(" ");
      }else{}
    }
    printf("\n");
  }

  return 0;
  fclose(infile);
}

