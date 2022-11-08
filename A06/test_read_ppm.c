#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
//  FILE* fr = fopen("feep-raw.ppm", "r");
//read_ppm open the file, we don't need to open two times
  int w,h;
  printf("Testing file feep-raw.ppm:");
  struct ppm_pixel* read = read_ppm("feep-raw.ppm",&w,&h);//ASK WHY IT HAS ERROR.
  for(int i =0; i<h;i++){
    for(int j=0;j<w;j++){
      printf("(%d,%d,%d)",read[i*w + j].red,read[i*w + j].green,read[i*w + j].blue);
    }
    printf("\n");
  }
  free(read);
  //fclose(fr);
  // load feep-raw and print out the grid of pixels
  return 0;
}