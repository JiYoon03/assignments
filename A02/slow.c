#include <stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
  int num;
  char buff[32];
  char* slowT;

  
  printf("Pause length: ");
  scanf("%d",&num);
  printf("Text: ");
  scanf("%s",buff);  
  
  slowT = (char*)malloc(num*strlen(buff)+strlen(buff)+1);
  int count =0;
  for(int i = 0; buff[i] != '\0'; ++i){
    slowT[count]=buff[i];
    count++;
    for(int j =0; j<num;j++){
      slowT[count]='.';
      count++;
    }
  }
  slowT[count] ='\0';
  printf("%s\n",slowT);
  free(slowT);

  return 0;
}
//make all
// valgrind ./slow