#include <stdio.h>

int main(void)
{
	// declare variables 

        char name[4];
        double cost;
        unsigned int flag;

	printf("Address of name: %p\n", &name);
	printf("Address of cost: %p\n", &cost);
	printf("Address of flag: %p\n", &flag);

	return 0;
}