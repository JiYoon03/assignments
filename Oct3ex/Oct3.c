#include <stdio.h>
#include <stdlib.h>

struct point {
  int x;
  int y;
};

int main() {
  struct point p[3];
  for (int i = 0; i < 3; i++) {
    p[i].x = i;
    p[i].y = 2*i;
  }

  FILE* fp = fopen("points.bin", "wb");//wrte binary
  fwrite(p, sizeof(struct point), 3, fp);
  fclose(fp); 
}

#include <stdio.h>
#include <stdlib.h>

struct point {
  int x;
  int y;
};

int main() {
  struct point p[3];

  FILE* fp = fopen("points.bin", "rb");//read binary
  fread(p, sizeof(struct point), 3, fp);
  fclose(fp); 

  for (int i = 0; i < 3; i++) {
    printf("p[%d] = (%d,%d)\n", i, p[i].x, p[i].y);
  }
}