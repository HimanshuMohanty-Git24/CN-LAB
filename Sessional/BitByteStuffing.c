#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 100

void bitStuffing(char in[])
{
    char stuff[MAXSIZE];
    char *p, *q;
    int count = 0;

    p = in;
    q = stuff;

    while (*p != '\0')
    {
        if (*p == '0')
        {
            *q = *p;
            q++;
            p++;
        }
        else
        {
            while (*p == '1' && count != 5)
            {
                *q = *p;
                q++;
                p++;
                count++;
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

    printf("\n----------------------------------------\n");
    printf("Bit Stuffing at Sender's End\n");
    printf("----------------------------------------\n");
    printf("The Stuffed character string is : %s\n", stuff);
}

void byteStuffing(char str[][MAXSIZE], int n)
{
    char frame[MAXSIZE][MAXSIZE];
    char flag[] = "flag";
    char esc[] = "esc";
    int k = 0;

    strcpy(frame[k++], flag);

    // Sender's end
    for (int i = 0; i < n; i++)
    {
        if (strcmp(str[i], flag) != 0 && strcmp(str[i], esc) != 0)
        {
            strcpy(frame[k++], str[i]);
        }
        else
        {
            strcpy(frame[k++], esc);
            strcpy(frame[k++], str[i]);
        }
    }

    strcpy(frame[k++], flag);

    printf("\n----------------------------------------\n");
    printf("Byte Stuffing at Sender's End\n");
    printf("----------------------------------------\n");
    printf("The Stuffed character string is : ");
    for (int i = 0; i < k; i++)
    {
        printf("%s\t", frame[i]);
    }

    printf("\n----------------------------------------\n");
    printf("Byte Destuffing at Receiver's End\n");
    printf("----------------------------------------\n");

    printf("The Destuffed character string is : ");
    int i = 0;
    while (i < k)
    {
        if (strcmp(frame[i], esc) == 0)
        {
            i++;
            if (strcmp(frame[i], esc) == 0)
            {
                printf("%s ", esc);
                i++;
            }
            else
            {
                printf("%s", frame[i]);
                i++;
            }
        }
        else
        {
            printf("%s ", frame[i]);
            i++;
        }
    }
    printf("\n");
}

int main()
{
    char in[MAXSIZE];
    char str[MAXSIZE][MAXSIZE];
    int n;

    printf("Enter the input character string (0's and 1's only): ");
    scanf("%s", in);

    printf("Enter the number of strings: ");
    scanf("%d", &n);

    printf("Enter the strings: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%s", str[i]);
    }

    printf("\nYou Entered : %s\n", in);
    printf("You Entered : ");
    for (int i = 0; i < n; i++)
    {
        printf("%s\t", str[i]);
    }

    bitStuffing(in);
    byteStuffing(str, n);

    return 0;
}