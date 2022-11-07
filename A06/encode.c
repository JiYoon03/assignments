#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  string filename = argv[1];
  int w,h;
  struct ppm_pixel* pixels = read_ppm(argv[1], &w, &h);
  Printf("Reading %s with width %d and height %d",filename,w,h);
  

  return 0;
}

