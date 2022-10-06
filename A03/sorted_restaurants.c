#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Restaurant{
 char name[30];
 int openH, closeH;
 float stars;
};
struct node{
 struct Restaurant r;
 struct node* next;
};

struct node* insert_sortedfront(struct Restaurant info, struct node* head) {
 struct node* new=malloc(sizeof(struct node));
 if(new == NULL) {//check the error
   printf("ERROR: Out of space!\n");
   exit(1);
 }
 strcpy(new->r.name,info.name);
 new->r.openH = info.openH;
 new->r.closeH = info.closeH;
 new->r.stars = info.stars;
 new->next = head; //new-head(NULL)
 head = new;//head(new)-head->next-NULL
 struct node* nexthead = head->next;//save head->next node
 if(nexthead!=NULL){//if head next node value is not NULL, then compare two restaurnats' stars
    float star1= head->r.stars;
    float star2= nexthead->r.stars;
    if(star1<star2){
      head->next = nexthead->next;
      nexthead->next=head;
      head=nexthead;
    }
 }
  return head;  
  free(new);//free malloc new
 }

void print(struct node* list) {
 for (struct node* j = list; j!= NULL; j = j->next) {
   printf("%s open: %d:00    close: %d:00    stars: %.1f\n",j->r.name,j->r.openH,j->r.closeH,j->r.stars);
 }
}
void clear(struct node* list){
  struct node* current = list;
  struct node* delete = list;
  while(current != NULL){
    current = current ->next;
    free(delete);
    delete = current;
  }
}

int main() {
  int resNum;
  printf("Enter a number of restaurants:");
  scanf("%d",&resNum);
  struct node* head=NULL;
  for(int i =0; i<resNum;i++){
    struct Restaurant r;
    printf("Enter a name: ");
    scanf(" %[^\n]%*c", r.name);
    printf("Open time: ");
    scanf("%d%*c",&r.openH); 
    printf("Close time: ");
    scanf("%d%*c",&r.closeH);
    printf("Stars: ");
    scanf("%f%*c",&r.stars);
    head = insert_sortedfront(r,head);
  }
  print(head);
  clear(head);
  return 0;
 }