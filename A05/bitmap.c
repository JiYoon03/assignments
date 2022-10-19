#include <stdio.h>
#include <stdlib.h>
void PrintBinary(int num);

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);
  printf("Let's check: %lx -> real number\n",img);
  unsigned long * elements = malloc(sizeof(unsigned long)*16);
  for(int i =0;i<16;i++){
   unsigned long ul = 0xF;
   unsigned long rightMostBit = (ul&img);
   elements[i]=rightMostBit;
   //printf("rightMostBit= %ld\n",rightMostBit);//checking collection int from right most bits
   img = (img>>4);
  }
  for(int j=15;j>=0;j--){
    //printf("leftMostBit= %ld\n",elements[j]);//checking collection int which change it rightmostBits to leftmostBits
    PrintBinary(elements[j]);
    if(j%2==0){
      printf("\n");
    }
  }
  return 0;
}
void PrintBinary(int num)
{	
	unsigned cnum = 1 << 31;
	int check = 0;
	while (cnum){
		if (cnum & num){
			printf("@ ");
			check = 1;
		}
		else{
			if (check != 0){
				printf("    ");
			}
		}
		cnum = cnum >> 1;
	}	
}
