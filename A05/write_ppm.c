#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement one

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
  FILE *fp = fopen(filename, "wb"); /* b - binary mode */
  fprintf(fp, "P6\n# Created by GIMP version 2.10.24 PNM plug-in\n%d %d\n255\n", w, h);
  for (int j = 0; j < h; ++j){
    for (int i = 0; i < w; ++i){
      struct ppm_pixel p = pixels[j*w+i]; 
      static unsigned char color[3];
        color[0]= p.red;
        color[1]= p.blue;
        color[2]= p.green;
      fwrite(color, 1, 3, fp);
    }
  }
  fclose(fp);
}

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}
