// 0x11223344(Hexadecimal) extract individual byte store it in variables and display

#include <stdio.h>

int main()
{
    int num = 0x11223344;
    int byte1 = 0, byte2 = 0, byte3 = 0, byte4 = 0;
    byte1 = num & 0x000000FF;         // 0xFF is used to mask the last 8 bits
    byte2 = (num & 0x0000FF00) >> 8;  // 0xFF00 is used to mask the 8 bits after the first 8 bits
    byte3 = (num & 0x00FF0000) >> 16; // 0xFF0000 is used to mask the 8 bits after the first 16 bits
    byte4 = (num & 0xFF000000) >> 24; // 0xFF000000 is used to mask the 8 bits after the first 24 bits
    printf("Byte1: %x\n", byte1);     //%x is used to print hexadecimal value
    printf("Byte2: %x\n", byte2);
    printf("Byte3: %x\n", byte3);
    printf("Byte4: %x\n", byte4);
    return 0;
}