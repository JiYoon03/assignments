#define _CRT_SECURE_NO_WARNINGS // strcpy warning
#include<stdio.h>
#include<string.h>
struct Restaurant{
  char name[30];
  int num, openH, closeH;
  float stars;
};

int main() {
int hr;
int resNum;
struct Restaurant s;
struct Restaurant t;
struct Restaurant m;   

printf("Welcome to JiYoon's Restarant List.\n");
printf("What hour is it (24 hr clock)? ");
scanf("%d",&hr);

strcpy(s.name, "Sushi Atsumi");
s.num = 0;
s.openH = 11;
s.closeH = 23;
s.stars = 3.5;

strcpy(t.name, "The Thirsty Horse");
t.num = 1;
t.openH = 17;
t.closeH = 2;
t.stars = 4.5;

strcpy(m.name, "Magic Bean Coffee");
m.num = 2;
m.openH = 6;
m.closeH = 15;
m.stars = 4.1;


printf("%d) %s open: %d:00    close: %d:00    stars: %.1f\n",s.num,s.name,s.openH,s.closeH,s.stars);
printf("%d) %s open: %d:00    close: %d:00    stars: %.1f\n",t.num,t.name,t.openH,t.closeH,t.stars);
printf("%d) %s open: %d:00    close: %d:00    stars: %.1f\n",m.num,m.name,m.openH,m.closeH,m.stars);
printf("What restaurant do you want to visit? [0,1,2]: ");
scanf("%d",&resNum);
if(resNum==s.num){
  if(hr>=s.openH&&hr<s.closeH){
    printf("Excellent choice. %s closed at %d o'clock!!\n",s.name,s.closeH - hr);
  }
  if(hr<s.openH){
    printf("%s isn't open until %d o'clock!!\n",s.name,s.openH);
  }
  if(s.closeH<hr){
    printf("%s closed at %d o'clock!!\n",s.name,s.closeH);
  }
}
if(resNum==t.num){
  if(hr>=t.openH&&hr<t.closeH){
    printf("Excellent choice. %s closed at %d o'clock!!\n",t.name,t.closeH - hr);
  }
  if(hr<t.openH){
    printf("%s isn't open until %d o'clock!!\n",t.name,t.openH);
  }
  if(t.closeH<hr){
    printf("%s closed at %d o'clock!!\n",t.name,t.closeH);
  }
}
if(resNum==m.num){
  if(hr>=m.openH&&hr<m.closeH){
    printf("Excellent choice. %s closed at %d o'clock!!\n",m.name,m.closeH - hr);
  }
  if(hr<m.openH){
    printf("%s isn't open until %d o'clock!!\n",m.name,m.openH);
  }
  if(m.closeH<hr){
    printf("%s closed at %d o'clock!!\n",m.name,m.closeH);
  }
}

  return 0;

}
