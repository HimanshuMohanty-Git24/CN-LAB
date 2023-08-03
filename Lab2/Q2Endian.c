// How byte is stored in the computer memory check if it’s little Endian or big endian

#include <stdio.h>

int main()
{
    unsigned int x = 0x76513210;
    char *c = (char *)&x;
    printf("0x%x\n", *c);
    if (*c == 0x10)
        printf("Little Endian\n");
    else
        printf("Big Endian\n");
    return 0;
}
