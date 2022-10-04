#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Restaurant{
  char name[30];
  int num, openH, closeH;
  float stars;
};
//%*c: When passed as part of a `scanf` format string, “%*c” means “read and ignore a character”. 
//There has to be a character there for the conversion to succeed, but other than that, the character is ignored. 
//A typical use-case would be reading up to some delimiter, then ignoring the delimiter. For example: char s[20];
int main() {
int resNum;
printf("Enter a number of restaurants:");
scanf("%d%*c",&resNum);
struct Restaurant* listR = malloc(sizeof(struct Restaurant) * resNum) ;
  for(int i =0; i<resNum;i++){
    printf("Enter a name: ");
    scanf(" %[^\n]%*c", listR[i].name);
    printf("Open time: ");
    scanf("%d%*c",&listR[i].openH); 
    printf("Close time: ");
    scanf("%d%*c",&listR[i].closeH);
    printf("Stars: ");
    scanf("%f%*c",&listR[i].stars);
  }
  for(int j=0;j<resNum;j++){
    printf("%d) %s open: %d:00    close: %d:00    stars: %.1f\n",j,listR[j].name,listR[j].openH,listR[j].closeH,listR[j].stars);
  }
  free(listR);
  return 0;}