#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int push(FILE* infile){//when encounter a '{'
 int[] open;
 while(fgetc(infile)!=EOF){//EOF is End Of File

 }
 return int open;
}
int pop(int end){//when user encounter a '}'
  return int j;
}


int main(int argc, char** argv) {
  FILE *infile;
  int linenum =0;//total number of line of infile
  char ch;
  if (argc != 1) {
    printf("usage: ./match_braces filename.c\n");
  }  
  infile = fopen(argv[1], "r");  // relative path name of file, read mode
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", argv[1]);
    exit(1);
  }
  while((ch = fgetc(infile))!=EOF) {
    putchar(ch);
    linenum++;
  }
  
  int start1,end1,start2,end2;
  printf("Found matching braces: (%d%*c,%d%*c)-->",&start1,&end2);
  fclose(infile);
  return 0;
}
