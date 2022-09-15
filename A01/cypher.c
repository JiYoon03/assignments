/**
*NULL character '\0'
*It is the character equivalent of integer 0(zero)
*it is generally used to mark an end of a string.
*/
#include<stdio.h>
#include<string.h>
int main() {
  char word[100], ch;
  int i, shift;
  printf("Enter a word:: ");
  scanf("%s",word);
  printf("Enter a shift: ");
  scanf("%d", &shift);
  //printf("%d\n",shift);
  for(i = 0; word[i] != '\0'; ++i){
    ch = word[i];
    if(ch >= 'a' && ch <= 'z'){
      ch = ch + shift;
    }
    if(ch < 'a'){
      ch = ch +'z'-'a' + 1;
    }
    if(ch > 'z'){
      ch = ch - 'z' + 'a' - 1;
    }
    word[i] = ch;
  }
  printf("Your cypher is %s\n",word);
 // printf("%ld\n",strlen(word));
  return 0;
}
