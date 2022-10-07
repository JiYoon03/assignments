#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"
//hexedit
//filename
//control C//to exit
// Choose *one* to implement
struct ppm_pixel {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  // open the file to read
  FILE* fr = fopen(filename, "r");
  if(!fr){//when filename is invalid
    return NULL;
  }
  // allocate array for pixels
  unsigned char* pixels = malloc(sizeof(unsigned char)*3* w * h);
  struct ppm_pixel* ppm = malloc(sizeof(struct ppm_pixel) * w * h);

  // formatted read of header
  int linenum=0;
  int countppm=0;
  int num=0;
  //num%3==0 red
  //num%3==1 green
  //num%3==2 blue
  while (fgets(pixels,3*w*h, fr) != EOF) {
    linenum++;
    if(linenum==3){
      printf("with width %s and height %s",pixels[0],pixels[2]);
    }
    if(linenum==5){//assume that line 5 always contains ppm
      int ppmhight = 0;
      while(ppmhight<h){
        int ppmwidth = 0;//everytime move to nextline, initalize ppmwidth
        while(ppmwidth<w){
          for(num;num<3*w*h;num++){
            if(num%3==0){//red
              ppm[ppmhight*w+ppmwidth].red = pixels[num];//ppm[0,0].r=pixels[0];
            }
            if(num%3==1){//green
              ppm[ppmhight*w+ppmwidth].green = pixels[num];
            }
            if(num%3==2){//blue
              ppm[ppmhight*w+ppmwidth].blue = pixels[num];
              ppmwidth++;//after put all of RGB then move to next ppm
            }
          }
        }//when ppmwidth become w then move to nextline of ppm
        ppmhight++;
      }
    }
  } // end of while

  return ppm;
  free(pixels);
  fclose(infile);
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}