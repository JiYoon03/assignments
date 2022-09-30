#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Restaurant{
 char name[30];
 int openH, closeH;
 float stars;
};
struct node{
 char name[30];
 int openH, closeH;
 float stars;
 struct node* next;
};
struct node* insert_front(struct Restaurant listR, struct node* head) {
 struct node* restlist = malloc(sizeof(struct node));
 if (restlist == NULL) {
   printf("ERROR: Out of space!\n");
   exit(1);
 }
 strcpy(restlist->name,listR.name);
 restlist->openH = listR.openH;
 restlist->closeH = listR.closeH;
 restlist->stars = listR.stars;
 restlist ->next = head;
 head = restlist;
 return head;
}

struct node* insert_sorted(struct node* head){
 if (head == NULL){
     return head;
 }
 struct node*now =head;
 struct node*then = head->next;
 while (now->next != NULL){
float small= now->stars;
float comp=then->stars;
	if(small>comp){
 now->next = then->next;
 then->next=now;
}
}
return head;
}

void print(struct node* list) {
 for (struct node* j = list; j->next != NULL; j = j->next) {
   printf("%s open: %d:00    close: %d:00    stars: %.1f\n",j->name,j->openH,j->closeH,j->stars);
 }
}
int main() {
int resNum;
struct node *head = NULL;;
printf("Enter a number of restaurants:");
scanf("%d",&resNum);
struct Restaurant* listR = malloc(sizeof(struct Restaurant) * resNum);
struct node* rest;
 for(int i =0; i<resNum;i++){
   printf("Enter a name: ");
   scanf(" %[^\n]%*c", listR[i].name);
   printf("Open time: ");
   scanf("%d%*c",&listR[i].openH);
   printf("Close time: ");
   scanf("%d%*c",&listR[i].closeH);
   printf("Stars: ");
   scanf("%f%*c",&listR[i].stars);
  rest = insert_front(listR[i],head);
 }  
 print(head);
 struct node* order;
 order = insert_sorted(rest);
 print(order);

 free(listR);
 return 0;
 }