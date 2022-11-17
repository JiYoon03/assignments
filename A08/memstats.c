#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "rand.h"

#define ROUNDS 3
#define BUFFER 5
#define LOOP 10

struct chunk {
  int size;
  int used;
  struct chunk *next;
};

void memstats(struct chunk* freelist, void* buffer[], int len) {
  int countfree =0;
  int countfreemem =0;
  struct chunk* nextfree;
  nextfree = freelist;
  while(nextfree->next!=NULL){
    countfree++;
    countfreemem += nextfree->size;
    nextfree = nextfree->next;
  }
  int countused =0;
  int countusedmem =0;
  double underutilizedmem =0.0;
  for(int i =0;i<len;i++){
    if(buffer[i]!=NULL){
      countused++;
      struct chunk *cnk = (struct chunk*)((struct chunk*)buffer[i] -1);//similiar as int* arr, arr+1
      countusedmem += cnk->size;
      double underutilizedmemIdx= (cnk->size)-(cnk->used);
      underutilizedmem+=underutilizedmemIdx;//finding unused memory each index and add into underutilizedmem
    }
  }
  int totalblock = countfree+countused;
  int totalmem = countfreemem+countusedmem;

  printf("Total blocks: %d Free blocks: %d Used blocks: %d\n",totalblock,countfree,countused);
  printf("Total memory allocated: %d Free memory: %d Used memory: %d\n", totalmem,countfreemem,countusedmem);
  printf("Underutilized memory: %f\n", underutilizedmem/totalmem);
}

int main ( int argc, char* argv[]) {

  printf("Starting test..\n");

  srand(100);

  double timer;
  struct timeval tstart, tend;

  gettimeofday(&tstart, NULL);

  void *buffer[BUFFER];
  for (int i = 0; i < BUFFER; i++) {
    buffer[i] = NULL;
  }

  void *init = sbrk(0);
  void *current;
  printf("The initial top of the heap is %p.\n", init);
  for (int j = 0 ; j < ROUNDS; j++) {
    printf("---------------\n%d\n" , j);

    for (int i= 0 ; i < LOOP ; i++) {
      int index = rand() % BUFFER;
      if (buffer[index] != NULL) {
        free(buffer[index]);
        buffer[index] = NULL;
        printf("Freeing index %d\n", index);
      } 
      else {
        size_t size = (size_t) randExp(8, 4000); 
        int *memory = NULL;
        memory = malloc(size);

        if (memory == NULL) {
          fprintf(stderr, "malloc failed\n");
          return(1);
        } 
        *memory = 123;
        buffer[index] = memory;
        printf("Allocating %d bytes at index %d\n", (int) size, index);
      }
    }
    extern struct chunk* flist;
    current = sbrk(0);
    int allocated = current - init;
    init = current;

    printf("The new top of the heap is %p.\n", current);
    printf("Increased by %d (0x%x) bytes\n", allocated, allocated);
    memstats(flist, buffer, BUFFER);
  }

  for (int i = 0; i < BUFFER; i++) {
    free(buffer[i]); 
  }
  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Time is %g\n", timer);

  return 0 ;
}
