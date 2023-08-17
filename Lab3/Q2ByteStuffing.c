// Wap to demonstrate byte stuffing and destuffing for a given frame(string) input by the user.

#include <stdio.h>
#include <string.h>
void main()
{
    char frame[50][50], str[50][50], destuffed[50][50];
    char flag[10];
    strcpy(flag, "flag");
    char esc[10];
    strcpy(esc, "esc");
    int i, j, k = 0, n;
    strcpy(frame[k++], "flag");
    printf("Enter length of String : \n");
    scanf("%d", &n);
    printf("Enter the String:\n ");
    for (i = 0; i <= n; i++)
    {
        gets(str[i]);
    }
    printf("\nYou entered :\n");
    for (i = 0; i <= n; i++)
    {
        puts(str[i]);
    }
    printf("\n");
    for (i = 1; i <= n; i++)
    {
        if (strcmp(str[i], flag) != 0 && strcmp(str[i], esc) != 0)
        {
            strcpy(frame[k++], str[i]);
        }
        else
        {
            strcpy(frame[k++], "esc");
            strcpy(frame[k++], str[i]);
        }
    }
    strcpy(frame[k++], "flag");
    printf("------------------------------\n\n");
    printf("Byte stuffing at sender side:\n\n");
    printf("------------------------------\n\n");
    for (i = 0; i < k; i++)
    {
        printf("%s\t", frame[i]);
    }
    printf("\n");

    // Destuffing
    k = 0;

    while (strcmp(frame[k], "flag") != 0)
    {
        k++;
    }
    k++;

    i = 0; // Counter for destuffed frame
    while (k < n)
    {
        if (strcmp(frame[k], "esc") == 0)
        {
            k++;
            strcpy(destuffed[i++], frame[k]);
        }
        else if (strcmp(frame[k], "flag") == 0)
        {
            break; // End of frame
        }
        else
        {
            strcpy(destuffed[i++], frame[k]);
        }
        k++;
    }

    // Display Destuffed Frame
    printf("------------------------------\n");
    printf("Byte destuffing at receiver side:\n");
    printf("------------------------------\n");
    for (j = 0; j < i; j++)
    {
        printf("%s\t", destuffed[j]);
    }
}
