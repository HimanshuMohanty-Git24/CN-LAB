// Wap to demonstrate bit stuffing and destuffing for a given frame(string) input by the user.
#include <stdio.h>
#include <string.h>
#define MAXSIZE 100
int main()
{
    char *p, *q;
    char temp;
    char in[MAXSIZE];
    char stuff[MAXSIZE];
    char destuff[MAXSIZE];
    int count = 0;
    printf("Enter the input character string(0's & 1's Only):");
    scanf("%s", in);
    p = in;
    q = stuff;
    while (*p != '\0')
    {
        if (*p == '0')
        {
            *q = *p;
            q++;
            p++;
            // count = 0;
        }
        else
        {
            while (*p == '1' && count != 5)
            {
                count++;
                *q = *p;
                q++;
                p++;
            }
            if (count == 5)
            {
                *q = '0';
                q++;
            }
            count = 0;
        }
    }
    *q = '\0';
    printf("The stuffed string is: %s\n", stuff);
    p = stuff;
    q = destuff;
    while (*p != '\0')
    {
        if (*p == '0')
        {
            *q = *p;
            q++;
            p++;
            // count = 0;
        }
        else
        {
            while (*p == '1' && count != 5)
            {
                count++;
                *q = *p;
                q++;
                p++;
            }
            if (count == 5)
            {
                p++; // skip the next 0
            }
            count = 0;
        }
    }
    *q = '\0';
    printf("The destuffed string is: %s\n", destuff);
    return 0;
}