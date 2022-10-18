//Sep 29 slide 25
unsigned char a =0xAB;
unsigned char leftMask = 0XF0;
unsigned char rightMask = 0X0F;

unsigned char left = (leftMask&a);
unsigned char right =(rightMask&a);
unsigned char leftShift = left>>4;
unsigned char rightShift = right<<4;
unsigned flipped = leftShift|rightShift;
printf("%04X",flipped);
