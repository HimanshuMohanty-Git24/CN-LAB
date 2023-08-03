// 0x11223344(Hexadecimal) extract individual byte store it in variables and display

#include <stdio.h>

int main()
{
    int num = 0x11223344;
    int byte1 = 0, byte2 = 0, byte3 = 0, byte4 = 0;
    byte1 = num & 0x000000FF;
    byte2 = (num & 0x0000FF00) >> 8;
    byte3 = (num & 0x00FF0000) >> 16;
    byte4 = (num & 0xFF000000) >> 24;
    printf("Byte1: %x\n", byte1);
    printf("Byte2: %x\n", byte2);
    printf("Byte3: %x\n", byte3);
    printf("Byte4: %x\n", byte4);
    return 0;
}