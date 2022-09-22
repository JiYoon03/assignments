#include <stdio.h>

int main() {
  int num[4][4];
  int largest=0;
  for(int i =0; i<4;i++){
    for(int j=0;j<4;j++){
      scanf("%d",&num[i][j]);
      if(j==3){
      printf("%d\n",num[i][j]);        
      }else{
      printf("%d ",num[i][j]);
      }
    }
  }
  for(int i =0; i<4;i++){
    for(int j=0;j<4;j++){
      if(num[i][j]==num[i][j+1]){ //check right
         if(largest<(num[i][j]+num[i][j+1])){
           largest = (num[i][j]+num[i][j+1]);
         }
     }
     if((num[i][j+1])==0){
      int a =j+1;
	      while(num[i][a]==0){
	        a++;
	      }
	    if(num[i][j]==num[i][a]&&(num[i][j]!=0)){ //check right for 0
        if(largest<(num[i][j]+num[i][a])){
          largest = (num[i][j]+num[i][a]);
         }
	      }
     }

      if(num[i][j]==num[i][j-1]){//check left
          if(largest<(num[i][j]+num[i][j-1])){
            largest = (num[i][j]+num[i][j-1]);
          }
      }

      if(num[i][j-1]==0){
        int a =j-1;
	      while(num[i][a]==0){
	        a--;
	      }
	    if(num[i][j]==num[i][a]&&(num[i][j]!=0)){ //check left for 0
        if(largest<(num[i][j]+num[i][a])){
          largest = (num[i][j]+num[i][a]);
         }
	      }
      }
      if(num[i][j]==num[i+1][j]){//check down
          if(largest<(num[i][j]+num[i+1][j])){
            largest = (num[i][j]+num[i+1][j]);
          }

      }
      if(num[i+1][j]==0){
           int a =i+1;
	      while(num[a][j]==0){
	        a++;
	      }
	    if(num[i][j]==num[a][j]&&(num[i][j]!=0)){ //check down for 0
        if(largest<(num[i][j]+num[a][j])){
          largest = (num[i][j]+num[a][j]);
         }
	      }
      }
      if(num[i][j]==num[i-1][j]){//check up
        if(largest<(num[i][j]+num[i-1][j])){
            largest = (num[i][j]+num[i-1][j]);
          }
	      }
      if(num[i-1][j]==0){
                 int a =i-1;
	      while(num[a][j]==0){
	        a--;
	      }
	    if(num[i][j]==num[a][j]&&(num[i][j]!=0)){ //check up for 0
        if(largest<(num[i][j]+num[a][j])){
          largest = (num[i][j]+num[a][j]);
         }
	      }
      }
    }
  }
  if(largest ==0){
    for(int i =0; i<4;i++){
      for(int j=0;j<4;j++){
        if(largest<(num[i][j])){
          largest = (num[i][j]);
         }
        }
      }
    }
  printf("The largest value is %d.\n",largest);
  return 0;
}
