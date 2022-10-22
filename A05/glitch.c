#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: glitch <file.ppm>\n");
    return 0;
  }
  int w,h;
  srand(time(0));
  struct ppm_pixel* pixels =read_ppm(argv[1],&w,&h);
  printf("Reading %s with width %d and height %d",argv[0],606,771);
  struct ppm_pixel* newcolorvalue = malloc(sizeof(struct ppm_pixel)*(606*771));
  for(int i=0;i<(606*771);i++){
    newcolorvalue[i].red = pixels[i].red << (rand() % 2);
    newcolorvalue[i].green = pixels[i].green << (rand() % 2);
    newcolorvalue[i].blue = pixels[i].blue << (rand() % 2);
  }
  write_ppm("monalisa-glitch.ppm",newcolorvalue, 606, 771);
  free(pixels);
  free(newcolorvalue);
  return 0;
}

