#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your code here 
  srand(time(0));
  int shmid;
  shmid = shmget(IPC_PRIVATE,sizeof(struct ppm_pixel)*size*size,0644| IPC_CREAT);
  if(shmid == -1){
    perror("Error: cannot initialize shared memory\n");
    exit(1);
  }
  struct ppm_pixel* color= shmat(shmid,NULL,0);
  if(color == (void*)-1){
    perror("Error: cannot access shared memory\n");
    exit(1);
  }
  int shmidpal;
  shmidpal = shmget(IPC_PRIVATE,sizeof(struct ppm_pixel)*size*size,0644| IPC_CREAT);
  if(shmid == -1){
    perror("Error: cannot initialize shared memory\n");
    exit(1);
  }
  struct ppm_pixel* palette= shmat(shmidpal,NULL,0);
  if(palette == (void*)-1){
    perror("Error: cannot access shared memory\n");
    exit(1);
  }
  for(int i=0;i<maxIterations;i++){
    palette[i].red = rand() % 255;
    palette[i].green = rand() % 255;
    palette[i].blue = rand() % 255;
  }  
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);
  
for(int parentGo =0;parentGo<4;parentGo++){
    int babexmin = 0;
    int babexmax = 0;
    int babeymin = 0;
    int babeymax = 0;
  switch(parentGo){
    case 0:
    babexmin = 0;
    babexmax = 240;
    babeymin = 0;
    babeymax = 240;
    break;
    case 1:
    babexmin = 240;
    babexmax = 480;
    babeymin = 0;
    babeymax = 240;  
    break;
    case 2:
    babexmin = 0;
    babexmax = 240;
    babeymin = 240;
    babeymax = 480;  
    break;  
    case 3:
    babexmin = 240;
    babexmax = 480;
    babeymin = 240;
    babeymax = 480;  
    break; 
  }
  int pid= fork();
  if(pid==0){
    printf("Launched child process:%d\n",getpid());
    printf("%d) Sub-image block: cols (%d,%d) to rows (%d,%d)\n",getpid(),babexmin,babexmax,babeymin,babeymax);
    for(int i =babexmin;i<babexmax;i++){//row
      for(int j =babeymin;j<babeymax;j++){//col
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
    printf("child process complete: %d\n",getpid());
    exit(0);
    }
  }
  for(int num =0;num<4;num++){
    int status;
    pid_t w = wait(&status);
  }
  gettimeofday(&tend, NULL);
  double  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  char* name= malloc(sizeof(char)*1000);
  sprintf(name,"multi-mandelbrot-%d-%lu.ppm",size,time(0));
  write_ppm(name, color, size, size);
  printf("Computed mandelbrot set (%dx%d) in %f seconds\n",size,size,timer); 
  printf("Writing file: %s\n",name);
  if(shmdt(color)==-1){
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }
  if(shmdt(palette)==-1){
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }
  if(shmctl(shmid,IPC_RMID,0)==-1){
    perror("Error: cannot remove shared memory\n");
    exit(1);
  }
  if(shmctl(shmidpal,IPC_RMID,0)==-1){
    perror("Error: cannot remove shared memory\n");
    exit(1);
  }
  free(name);
}
