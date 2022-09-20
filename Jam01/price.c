//Abby&Ria&Syarah

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main() {
  srand(time(0));
  int myguess;
  int price = 3000;
  int a = rand()%2001;
  int ai1 = 3000+(rand()%2001);
  int ai2= 3000+(rand()%2001);
  price = price + a;
  printf("Welcome to the Price is Right!");
  printf("Enter a guess to win a luxurious dishwasher: ");
  scanf("%d",&myguess);
  printf("AI contestant #1 guesses %d\n",ai1);
  printf("AI contestant #2 guesses %d\n",ai2);
  int me = price - myguess;
  int a1=price -ai1;
  int a2 = price - ai2;
  printf("The dishwasher cost %d\n",price);
if(me>0 && me < a1 && me < a2){
  printf("You win\n");
}
else if(a1>0 && a1 < me && a1 < a2){
  printf("A1 win\n");
}
else if(a2>0 && a2 < me && a2 < a1){
   printf("A2 win\n");
}
else{
   printf("Nobody wins\n");
}
  return 0;
}

