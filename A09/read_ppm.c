#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  // open the file to read
  FILE* fr = fopen(filename, "rb");//read binary file in c: "rb"
  if(!fr){//when filename is invalid
    return NULL;
  }
  // allocate array for pixels
  //ch2 pointer parameter
  char line[1240];
  fgets(line,1240,fr);//p6
  printf("%s",line);
  fgets(line,1240,fr);//#~~
  printf("%s",line);
  fscanf(fr,"%d %d\n",w,h);
  printf("%d %d\n",*w,*h);
  struct ppm_pixel* ppm = malloc(sizeof(struct ppm_pixel)*(*w)*(*h));
  for(int i=0;i<(*w**h);i++){
    ppm[i].red=0;
    ppm[i].blue=0;
    ppm[i].green=0;
  }//don't need to do it bc fread initialized
  fgets(line,1240,fr);
  fread(ppm,sizeof(struct ppm_pixel),((*w)*(*h)),fr);
  fclose(fr);
  return ppm;

}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {

  return NULL;
}
