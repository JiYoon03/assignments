#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

pthread_mutex_t mutex;
pthread_barrier_t barrier; // the barrier synchronization object


struct thread_data
{
  int size;
  float xmin;
  float xmax;
  float ymin;
  float ymax;
  int maxIterations;
  int numProcesses;
  int id;    
  struct ppm_pixel* color;//how to setup color
  struct ppm_pixel* palette;
  int* membership;
  int* increment;
  int max_count;
  int babexmin;
  int babexmax; 
  int babeymin;
  int babeymax;
};

void *tstepOne(void *userdata){
  struct thread_data *data =(struct thread_data*) userdata;
  for(int i =data->babexmin;i<data->babexmax;i++){//row
      for(int j =data->babeymin;j<data->babeymax;j++){//col
       float xfrac = (float)j/data->size; //col/image_size
       float yfrac = (float)i/data->size;//row/image_size
       float xo = data->xmin + xfrac * ((data->xmax)-(data->xmin));
       float yo = data->ymin + yfrac * ((data->ymax)-(data->ymin));
      float x=0;
      float y=0;
      int iter = 0;
      while (iter<(data->maxIterations) && x*x + y*y <2*2){
        float xtmp = x*x -y*y +xo;
        y = 2*x*y+yo;
        x = xtmp;
        iter++;
      }
      if(iter<(data->maxIterations)){
        data->membership[i*data->size+j] = 0;//false
      }else{
        data->membership[i*data->size+j] = 1;//true
      }
     }
    }
    return (void*)NULL;
}
void *tstepTwo(void *userdata){
  struct thread_data *data =(struct thread_data*) userdata;
  for(int i =data->babexmin;i<data->babexmax;i++){//row
      for(int j =data->babeymin;j<data->babeymax;j++){//col
        if(data->membership[i*data->size+j]==1){
          continue;
        }else{
         float xfrac = (float)j/data->size; //col/image_size
         float yfrac = (float)i/data->size;//row/image_size
         float xo = data->xmin + xfrac * ((data->xmax)-(data->xmin));
         float yo = data->ymin + yfrac * ((data->ymax)-(data->ymin));
         float x=0;
         float y=0;
         while (x*x + y*y <2*2){
           float xtmp = x*x -y*y +xo;
           y = 2*x*y+yo;
           x = xtmp;
           int yrow = round(data->size*(y-data->ymin)/(data->ymax-data->ymin));
           int xcol = round(data->size*(x-data->xmin)/(data->xmax-data->xmin));
           if(yrow<0||yrow>=data->size){
             continue;
           }
           if(xcol<0||xcol>=data->size){
             continue;
           }
           pthread_mutex_lock(&mutex);
           data->increment[yrow*data->size+xcol]++;
           if(data->increment[yrow*data->size+xcol]>data->max_count){
             data->max_count=data->increment[yrow*data->size+xcol];
           }
           pthread_mutex_unlock(&mutex);
         }
        }
     }
  }
  return (void*)NULL;
}
void *tstepThree(void *userdata){
  float gamma = 0.681;
  float factor = 1.0/gamma;
  struct thread_data *data =(struct thread_data*) userdata;
  for(int i =data->babexmin;i<data->babexmax;i++){//row
      for(int j =data->babeymin;j<data->babeymax;j++){//col
       float value = 0;
       if(data->increment[i*data->size+j]>0){
         value = log(data->increment[i*data->size+j])/log(data->max_count);
         value = pow(value,factor);
       }
       data->color[i*data->size+j].red = value *255;
       data->color[i*data->size+j].green = value *255;
       data->color[i*data->size+j].blue = value *255;
     }
    }
    return (void*)NULL;
}
void *start(void *userdata){
  struct thread_data *data =(struct thread_data*) userdata;
  tstepOne((void*)userdata);
  tstepTwo((void*)userdata);
  pthread_barrier_wait (&barrier);
  tstepThree((void*)userdata);
  printf("Thread %d) finished\n",(data->id+1));
  return (void*)NULL;
}

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
  srand(time(0));

// todo: your code here
 struct ppm_pixel* palette= malloc(sizeof(struct ppm_pixel)*maxIterations);
 struct ppm_pixel* color= malloc(sizeof(struct ppm_pixel)*size*size);
  for(int i=0;i<maxIterations;i++){
    palette[i].red = rand() % 255;
    palette[i].green = rand() % 255;
    palette[i].blue = rand() % 255;
  }
  struct timeval tstart, tend;  
  pthread_t allthread[4];//store all thread-data//id of thread
  struct thread_data *thread_args = malloc(4 * sizeof(struct thread_data));
  int* membership = malloc(sizeof(int)*size*size);
  int* increment = malloc(sizeof(int)*size*size);
  for (int num =0;num<size*size;num++){
    increment[num]=0;
  }

  gettimeofday(&tstart, NULL);
  pthread_mutex_init(&mutex,NULL);
  pthread_barrier_init (&barrier, NULL, 4);
  for (int t = 0; t < 4; t++) {
   thread_args[t].id = t;
   thread_args[t].palette = palette;
   thread_args[t].color = color;
   thread_args[t].size = 480;
   thread_args[t].xmin = -2.0;
   thread_args[t].xmax = 0.47;
   thread_args[t].ymin = -1.12;
   thread_args[t].ymax = 1.12;
   thread_args[t].maxIterations = 1000;
   thread_args[t].numProcesses = 4;
   thread_args[t].membership = membership;
   thread_args[t].increment =increment;
   thread_args[t].max_count=0;
    switch(t){
    case 0:
    thread_args[t].babexmin = 0;
    thread_args[t].babexmax = 240;
    thread_args[t].babeymin = 0;
    thread_args[t].babeymax = 240;
    break;
    case 1:
    thread_args[t].babexmin = 240;
    thread_args[t].babexmax = 480;
    thread_args[t].babeymin = 0;
    thread_args[t].babeymax = 240;  
    break;
    case 2:
    thread_args[t].babexmin = 0;
    thread_args[t].babexmax = 240;
    thread_args[t].babeymin = 240;
    thread_args[t].babeymax = 480;  
    break;  
    case 3:
    thread_args[t].babexmin = 240;
    thread_args[t].babexmax = 480;
    thread_args[t].babeymin = 240;
    thread_args[t].babeymax = 480;  
    break; 
    }
    printf("Thread %d) sub-image block: cols (%d, %d) to rows (%d, %d)\n",t+1,thread_args[t].babexmin,thread_args[t].babexmax,thread_args[t].babeymin,thread_args[t].babeymax);
    pthread_create(&allthread[t], NULL, start,(void*) &thread_args[t]);//address pointer
  }
  for(int x=0;x<4;x++){
    pthread_join(allthread[x],NULL);
  }
  gettimeofday(&tend, NULL);
  double  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  char* name= malloc(sizeof(char)*1000);
  sprintf(name,"buddhabrot-%d-%lu.ppm",size,time(0));
  write_ppm(name, color, size, size);
  printf("Computed buddhabrot set (%dx%d) in %f seconds\n",size,size,timer);
  printf("Writing file: %s\n",name);
  pthread_mutex_destroy(&mutex);
  pthread_barrier_destroy(&barrier);
  free(color);
  free(palette);
  free(name);
  free(thread_args);
  free(membership);
  free(increment);
}