#include <stdio.h>
#include <string.h>
#include <time.h>
#include "words.h" // header that defined chooseWord()

int main() {
  srand(time(0));
  const char* word = chooseWord();
  printf("cheat: %s\n", word);
  int fail=0;
  for(int try=6;try>0;try--){
    int correct =0;
    char guess[5];
    printf("%d chance left. Please enter a 5-letter word: ",try);
    scanf("%s",guess);
    for(int i=0;i<5;i++){
      //printf("%d:",i);
      if(word[i]==guess[i]){
          printf("%c is in the word AND in the correct spot!\n",guess[i]);
          correct+=1;
      }else{
        for(int j=0;j<5;j++){
          //printf("%d:",j);
          if((word[j]==guess[i])&&(i!=j)){
            printf("%c is in the word (but not in the correct spot)!\n",guess[i]);
            j = 6;
          }
          if(j==4){
            printf("%c is NOT in the word.\n",guess[i]);
          }
        }
      }
    }
    if(correct==5){
      printf("You guessed it! The word is %s\n",word);
      fail+=1;
    }
   
  } if(fail==0){
      printf("Sorry, you ran out of tries. The word is %s\n",word);
    }
  return 0;
}
