#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Restaurant{
  char name[30];
  int num, openH, closeH;
  float stars;
};
int main() {
int resNum;
printf("Enter a number of restaurants:");
scanf("%d",&resNum);
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