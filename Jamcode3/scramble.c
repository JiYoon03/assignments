#include <stdio.h>
#include <string.h>
int main(){
    char ascii_str[1000];
    char ascii_chan[1000];
    printf("Please enter a phrase:");
    scanf("%[^\n]s\n",ascii_str);
    int len = strlen(ascii_str);
    int i;
    //printing
    printf("ascii_str: %s\n", ascii_str);
    printf("byte array is...\n");
    for(i=0; i<(len); i++)
    {
        printf("%c - %x\n", ascii_str[i], ascii_str[i]);
        unsigned char mask1= 0x8;
        unsigned char mask2= 0x04;
        printf("%x\n",mask1&ascii_str[i]);
        printf("%x\n",mask2&ascii_str[i]);
        unsigned char c1 =mask1&ascii_str[i];
        unsigned char c2 =mask2&ascii_str[i];
        unsigned char mask3 = 0xf3;
        unsigned char c3 =mask3&ascii_str[i];
        if(c1==0x8){
            c1=c1>>1;
        }
        if(c2==0x4){
            c2=c2<<1;
        }
        
        ascii_chan[i]=c3|c1|c2;
        printf("%c - %x\n", ascii_chan[i], ascii_chan[i]);

    }

     for(i=0; i<(len); i++)
    {  
        printf("%c", ascii_chan[i]);
    } 
    printf("\n");
    return 0;
}