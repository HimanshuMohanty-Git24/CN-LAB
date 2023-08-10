// Wap to demonstrate byte stuffing and destuffing for a given frame(string) input by the user.
#include <stdio.h>
#include <string.h>

int main()
{
    char frame[50][50], str[50][50];
    char flag[10];
    strcpy(flag, "flag");
    char esc[10];
    strcpy(esc, "esc");
    int i, j, k = 0, n;

    printf("Enter the number of strings: ");
    scanf("%d", &n);
    getchar();

    printf("Enter the strings:\n");
    for (i = 0; i < n; i++)
    {
        fgets(str[i], sizeof(str[i]), stdin);
        str[i][strcspn(str[i], "\n")] = '\0';
    }

    printf("You Entered:\n");
    for (i = 0; i < n; i++)
    {
        puts(str[i]);
    }

    for (i = 0; i < n; i++)
    {
        strcpy(frame[k++], esc);
        for (j = 0; j < strlen(str[i]); j++)
        {
            if (str[i][j] == esc[0] || str[i][j] == flag[0])
            {
                strcpy(frame[k++], esc);
            }
            char temp[2] = {str[i][j], '\0'};
            strcpy(frame[k++], temp);
        }
        strcpy(frame[k++], esc);
    }

    printf("\n-------------------------------\n");
    printf("Byte stuffing at sender side:\n\n");
    printf("--------------------------------\n");
    for (i = 0; i < k; i++)
    {
        printf("%s ", frame[i]);
    }
    printf("\n");

    printf("-------------------------------\n");
    printf("Byte destuffing at receiver side:\n\n");
    printf("--------------------------------\n");

    i = 0;
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
    return 0;
}
