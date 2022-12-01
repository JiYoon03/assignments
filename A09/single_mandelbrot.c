#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);
   struct ppm_pixel* palette= malloc(sizeof(struct ppm_pixel)*maxIterations);
 struct ppm_pixel* color= malloc(sizeof(struct ppm_pixel)*size*size);
  srand(time(0));
  for(int i=0;i<maxIterations;i++){
    palette[i].red = rand() % 255;
    palette[i].green = rand() % 255;
    palette[i].blue = rand() % 255;
  }  
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);
  // todo: your work here
  for(int i =0;i<size;i++){//row
    for(int j =0;j<size;j++){//col
      float xfrac = (float)j/size; //col/image_size
      float yfrac = (float)i/size;//row/image_size
      float xo = xmin + xfrac * (xmax-xmin);
      float yo = ymin + yfrac * (ymax-ymin);
 
      float x=0;
      float y=0;
      int iter = 0;
      while (iter<maxIterations && x*x + y*y <2*2){
        float xtmp = x*x -y*y +xo;
        y = 2*x*y+yo;
        x = xtmp;
        iter++;
      }
     
      if(iter<maxIterations){
        color[i*size+j] = palette[iter];
      }else{
        color[i*size+j].red =0;
        color[i*size+j].blue =0;
        color[i*size+j].green =0;
      }
     }
    }
    
  gettimeofday(&tend, NULL);
  double  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  char* name= malloc(sizeof(char)*1000);
  sprintf(name,"multi-mandelbrot-%d-%lu.ppm",size,time(0));
  write_ppm(name, color, size, size);
  printf("Computed mandelbrot set (%dx%d) in %f seconds\n",size,size,timer);
  printf("Writing file: %s\n",name);
  free(color);
  free(palette);
  free(name);
}
