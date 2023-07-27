// Wap to swap 2 string which are accepted through cmd line arguments that comes from argv[]

#include <stdio.h>
#include <string.h>

void swapStrings(char **str1, char **str2)
{
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Need only 2 argumnet to swap !!!");
    }
    else
    {
        char *string1 = argv[1];
        char *string2 = argv[2];

        printf("Before swapping: string1 = %s, string2 = %s\n", string1, string2);

        swapStrings(&string1, &string2);

        printf("After swapping: string1 = %s, string2 = %s\n", string1, string2);
    }

    return 0;
}
