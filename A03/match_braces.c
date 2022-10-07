#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//QUESTION: unable to open the file (line:66)
//check fgetc function work (line:75)
//make sure "n" able to check \n (line:79)
//ask clear function is correct(line:57)

//HELPFUL TO UNDERSTAND THE BIG PICTURE OF MATCH_BRACES.C:
//Found matching braces: (21, 32) -> (23, 5)
//means line 21 and char[32] has { line 23 and char[5]
//use countline and countchar also understand to use \n
//two stack:open & close
//matching 
//function of the clear//stack pointer remover/free

struct Braces{
  int line;
  int charnum;
};
typedef struct stack{
  int top;//top of index
  struct Braces *data;//ptr of index
  int max;//maxsize
}stack;
//initialize stack
void StackInitialize(struct stack* stk, int size){
  stk->data = malloc(sizeof(struct Braces));
  stk->top = -1;
  stk->max = size;
}

//when encounter a '{' use push to save line and char
void push(stack* stk,struct Braces brace){
  if(stk->top <stk->max-1){//ex) top =-1
    stk->top++;//ex)top=0;
    stk->data[stk->top]= brace;//ex)stk->data[0]=struct Braces open;
  }
}

//when encounter a '{' use pop to return line and char value
void pop(stack* stk){
  if(stk->top>=0){
    struct Braces b= stk->data[stk->top];
    stk->top--;
    printf("(%d,%d)",b.line,b.charnum);
  }
}

//check stack is empty
int isEmpty(stack* stk){
  if(stk->top==-1){
    return 1;//true
  }
  return 0;//false
}
//delete all data in stack
void clear(stack *stk){
  stk->top=0; 
  return; 
}

int main(int argc, char** argv) {
  FILE *infile;
  //maxline & max char in lines & helper for finding maxchar
  int maxline=0;
  int maxchar=0;
  int numchar=0;
  int bracesline=1;
  char ch;
  //Print the usage if the user inputs an incorrect number of command line arguments
  if (argc != 1) {
    printf("usage: ./match_braces filename.c\n");
  }  
  infile = fopen(argv[1], "r");

  // relative path name of file, read mode
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", argv[1]);
    exit(1);
  }
//find maxline & maxchar

//////////////////////////ASK is this is right way to read infile??
  while((ch = fgetc(infile))!=EOF) {//EOF is End Of File
    //no confues! fgetc/fgets: fgetc(FILE* infile) || fgets(char,int num,FILE)
    //find maxline and maxchar
    numchar++;
    if(ch=='\n'){
      maxline++;
      if(numchar>maxchar){//if currentline numchar is bigger than maxchar 
        maxchar=numchar;//update maxchar as currentline numchar
      }
      numchar=0;//reset numchar for nextline
    }
  }
  
  numchar=0;//initalize numchar for no error
  struct Braces open;
  struct Braces close;
  struct stack openbraces;
  StackInitialize(&openbraces,maxline);
  struct stack closebraces;
  StackInitialize(&closebraces,maxline); 
  while((ch=fgetc(infile))!=EOF){
    numchar++;
    if(ch=='{'){//when find { push it to openbraces stack
      open.line=bracesline;
      open.charnum=numchar;
      push(&openbraces,open);
    }
    if(ch=='}'){//when find } push it to closebrace stack
      close.line=bracesline;
      close.charnum=numchar;
      push(&closebraces,close);   
      if(!isEmpty(&openbraces)&&!isEmpty(&closebraces)){//both is not empty
        printf("Found matching braces:");
        pop(&openbraces);
        printf("->");
        pop(&closebraces);
        printf("\n");
      }
      if(!isEmpty(&openbraces)&&isEmpty(&closebraces)){//openbraces is not empty but closebraces is empty
        printf("Unmatched brace on (Line,Column): ");
        pop(&openbraces);
        printf("\n");
      }
      if(!isEmpty(&closebraces)&&isEmpty(&openbraces)){//closebraces is not empty but closebraces is empty
        printf("Unmatched brace on (Line,Column): ");
        pop(&closebraces);
        printf("\n");
      }
    }
    if(ch=='\n'){
      bracesline++;
      numchar=0;//reset numchar for nextline
    }
  }
  clear(&closebraces);
  clear(&openbraces);
  fclose(infile);
  return 0;
}
