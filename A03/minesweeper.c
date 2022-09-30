#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
//[i*n + j] works same as [i][j]
int main(int argc, char** argv) {
  srand(time(0));
  if (argc != 4) {
    printf("usage: %s m n p\n", argv[0]);
  }
  int m;//row 
  m = atoi(argv[1]);//convert string to int/float
  int n;//col
  n = atoi(argv[2]);
  float p;
  p = atof(argv[3]);
  printf("percentage of bomb is %f.",p);
  int percent = p*10;
  //printf("%d",percent); test for checking
  char * makebomb;
  makebomb = (char*)malloc((n*m)*sizeof(char)+1);
  for(int i =0; i<m;i++){
    for(int j=0;j<n;j++){
      int per = rand()%10;
      makebomb [i*n + j] = per;
    }
  }
  makebomb[n*m] ='\0';
  char * bomb;
  bomb = (char*)malloc((n*m)*sizeof(char)+1);
  printf("test\n");
   for(int i =0; i<m;i++){
    for(int j=0;j<n;j++){
      //printf("%d",bomb[i*n + j]);
        if(makebomb[i*n + j]>percent){
       printf(".");
       bomb[i*n + j]='.';
      }else{
        printf("X");
        bomb[i*n + j]='X';
      }
    }
    printf("\n");
  }
  printf("number of neighboring bombs:\n");
//ASK QUESTION ABOUT IT
//unable to print out accurate neighboring bombs
  for(int i =0; i<m;i++){
    for(int j=0;j<n;j++){
      int neig = 0;
      int num = i*n + j;
    if(bomb[num]=='X'){
      printf("X");
    }else{
    if(num%n!=(n-1)&&bomb[num+1]=='X'){//check num is not end of right side & n= #col & check right
      neig++;
    }
    if(num%n!=0&&bomb[num-1]=='X'){//check num is not end of left side & check left
      neig++;
    }
    if((num+n)<(m*n)&&bomb[num+n]=='X'){//check limition & check up
      neig++;
    }
    if(num%n!=(n-1)&&(num+n)<(m*n)&&bomb[num+n+1]=='X'){//check up right
      neig++;
    }
    if(num%n!=0&&(num+n)<(m*n)&&bomb[num+n-1]=='X'){//check up left
      neig++;
    }    
    if((num-n)>0&&bomb[num-n]=='X'){//check limition & check down
      neig++;
    }
    if(num%n!=(n-1)&&(num-n)>0&&bomb[num-n+1]=='X'){//check down right
      neig++;    
    }
    if(num%n!=0&&(num-n)>0&&bomb[num-n-1]=='X'){//check down left
      neig++;    
    }
      printf("%d",neig);
    }
    }
    printf("\n");
  }
  free(makebomb);
  free(bomb);
  return 0;
}

